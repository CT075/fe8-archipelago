{-# LANGUAGE AllowAmbiguousTypes #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE TypeApplications #-}
{-# LANGUAGE TypeOperators #-}
{-# LANGUAGE UndecidableInstances #-}
{-# OPTIONS_GHC -Werror=incomplete-patterns #-}

-- The main purpose of this file is to generate both the necessary C header
-- (for building the ROM) and a python module defining the relevant types (for
-- the client to communicate with the ROM).
--
-- By generating both files from a common source, we can ensure that they never
-- drift out of sync, and also means that this file can serve as a single point
-- of reference for such events.
--
-- CR-someday cam: Bringing in the whole Haskell datatype machinery is kind of
-- overkill. A simpler design would simply to have some kind of data file
-- listing the names of each location (etc) and simply have this file read it.
-- I'm a bit loathe to do that because we'd either have to come up with some
-- common data interface for all the different categories (e.g. PutHolyWeapon vs
-- ProgressiveWLv) or design a DSL to express them, whereas this file makes that
-- structure very "obvious" once you know which type declarations to look at.

import Control.Monad (forM_)
import Data.List
import GHC.Generics
import System.Environment (getArgs)
import System.Exit (ExitCode (..), exitWith)
import System.IO (hPutStrLn, stderr)
import Text.Read (readMaybe)
import Type.Reflection

-------------------- Generics Magic --------------------

-- Note to maintainers: Don't touch anything in this section unless you already
-- understand how GHC.Generics works.

-- This machinery is intended to automatically generate proper [Enum] instances
-- from the definitions of [Location] and [Item]. Using [GHC.Generics] to do
-- this is a bit like pulling out a bazooka to kill a fly, but it saves us from
-- having to manually write error-prone index-shifting logic every time we add
-- a new variant.

class GBoundedEnum t where
  gtoEnum :: Int -> t p
  gfromEnum :: t p -> Int

  gminBound :: t p
  gmaxBound :: t p

instance (Bounded k, Enum k) => GBoundedEnum (K1 a k) where
  gtoEnum i = K1 $ toEnum i
  gfromEnum (K1 k) = fromEnum k

  gminBound = K1 $ minBound
  gmaxBound = K1 $ maxBound

  {-# INLINE gtoEnum #-}
  {-# INLINE gfromEnum #-}
  {-# INLINE gminBound #-}
  {-# INLINE gmaxBound #-}

instance (GBoundedEnum l, GBoundedEnum r) => GBoundedEnum (l :+: r) where
  gtoEnum i =
    if i <= gfromEnum (gmaxBound @l)
      then L1 $ gtoEnum @l i
      else R1 $ gtoEnum @r (i - (gfromEnum (gmaxBound @l) + 1))

  gfromEnum (L1 l) = gfromEnum l
  gfromEnum (R1 r) = gfromEnum r + (gfromEnum (gmaxBound @l)) + 1

  gminBound = L1 $ gminBound @l
  gmaxBound = R1 $ gmaxBound @r

  {-# INLINE gtoEnum #-}
  {-# INLINE gfromEnum #-}
  {-# INLINE gminBound #-}
  {-# INLINE gmaxBound #-}

instance (GBoundedEnum k) => GBoundedEnum (M1 _a _b k) where
  gtoEnum i = M1 $ gtoEnum i
  gfromEnum (M1 x) = gfromEnum x
  gminBound = M1 $ gminBound
  gmaxBound = M1 $ gmaxBound

  {-# INLINE gtoEnum #-}
  {-# INLINE gfromEnum #-}
  {-# INLINE gminBound #-}
  {-# INLINE gmaxBound #-}

instance GBoundedEnum V1 where
  gtoEnum = error "attempted to construct [V1] via [gtoEnum]"
  gfromEnum = undefined
  gminBound = undefined
  gmaxBound = undefined

instance GBoundedEnum U1 where
  gtoEnum 0 = U1
  gtoEnum i = error $ "got index " ++ show i ++ " out of bounds when constructing enum"

  gfromEnum U1 = 0

  gminBound = U1
  gmaxBound = U1

  {-# INLINE gtoEnum #-}
  {-# INLINE gfromEnum #-}
  {-# INLINE gminBound #-}
  {-# INLINE gmaxBound #-}

-- We need a newtype wrapper to avoid orphaning the instances here.
-- Alternatively, we could use DerivingVia, but I don't want to figure that
-- out right now..
data BE a = BE {unBE :: a}

instance (Generic a, GBoundedEnum (Rep a)) => Enum (BE a) where
  toEnum = BE . to . gtoEnum
  fromEnum = gfromEnum . from . unBE

instance (Generic a, GBoundedEnum (Rep a)) => Bounded (BE a) where
  minBound = BE $ to gminBound
  maxBound = BE $ to gmaxBound

-------------------- end Generics Magic --------------------

data HolyWeapon
  = Sieglinde
  | Siegmund
  | Gleipnir
  | Garm
  | Nidhogg
  | Vidofnir
  | Excalibur
  | Audhulma
  | Ivaldi
  | Latona
  deriving (Show, Enum, Bounded, Typeable, Generic)

-- holyWeaponShort :: HolyWeapon -> String
-- holyWeaponShort = show @HolyWeapon

holyWeaponLong :: HolyWeapon -> String
holyWeaponLong = (++ " Received") . show @HolyWeapon

-- CR-soon cam: Instead of doing this, we should make [FillerItem] a newtype of
-- [Int] and simply include the item ID.
data FillerItem
  = AngelicRobe
  | EnergyRing
  | SecretBook
  | Speedwings
  | GoddessIcon
  | DragonShield
  | Talisman
  | BodyRing
  | Boots
  | KnightCrest
  | HeroCrest
  | OrionsBolt
  | GuidingRing
  | ElysianWhip
  | OceanSeal
  | MasterSeal
  deriving (Show, Enum, Bounded, Typeable, Generic)

data Chapter
  = Prologue
  | -- For now, we treat Eirika and Ephraim versions of the same map as the
    -- same location
    C Int
  | Tower Int
  | Ruins Int
  | C5x
  | Endgame1
  | Endgame2
  deriving (Show, Typeable, Eq)

-- apparently this isn't in my version of base?
(!?) :: [a] -> Int -> Maybe a
[] !? _ = Nothing
(x : _) !? 0 = Just x
(_ : xs) !? n = xs !? (n - 1)

allChapters :: [Chapter]
allChapters =
  {- HLINT refact:Evaluate -}
  []
    ++ [Prologue]
    ++ (C <$> [1 .. 5])
    ++ [C5x]
    ++ (C <$> [6 .. 20])
    ++ [Endgame1, Endgame2]
    ++ (Tower <$> [1 .. 8])
    ++ (Ruins <$> [1 .. 10])

-- We can't use [GBoundedEnum] here because we have custom bounds on the [Int]s
-- in [C], [Tower] and [Ruins].
instance Bounded Chapter where
  minBound = head allChapters
  maxBound = last allChapters

instance Enum Chapter where
  toEnum i =
    case allChapters !? i of
      Just c -> c
      Nothing -> error $ "invalid chapter index " ++ show i

  fromEnum c =
    case findIndex (== c) allChapters of
      Just i -> i
      Nothing ->
        error $ "[Chapter::fromEnum] BUG: " ++ show c ++ " missing from [allChapters]"

data Location
  = ChapterClear Chapter
  | HolyWeaponGet HolyWeapon
  deriving (Show, Typeable, Generic)

-- Having to manually construct this instance could be done away with via
-- TemplateHaskell, but that's using a bazooka to kill a fly at this point.
instance Bounded Location where
  minBound = unBE $ minBound @(BE _)
  maxBound = unBE $ maxBound @(BE _)

instance Enum Location where
  toEnum = unBE . toEnum @(BE _)
  fromEnum = fromEnum @(BE _) . BE

data WeaponType
  = Sword
  | Lance
  | Axe
  | Bow
  | Staff
  | Anima
  | Light
  | Dark
  deriving (Show, Enum, Bounded, Typeable, Generic)

data Item
  = ProgressiveLevelCap
  | ProgressiveWLv WeaponType
  | HolyWeaponPut HolyWeapon
  | FillerPlacement FillerItem
  deriving (Show, Typeable, Generic)

instance Bounded Item where
  minBound = unBE $ minBound @(BE _)
  maxBound = unBE $ maxBound @(BE _)

-- CR-someday cam: we should be able to generate this
instance Enum Item where
  toEnum = unBE . toEnum @(BE _)
  fromEnum = fromEnum @(BE _) . BE

itemName :: Item -> String
itemName ProgressiveLevelCap = "Progressive Level Cap"
itemName (ProgressiveWLv weap) = "Progressive Weapon Level (" ++ show weap ++ ")"
itemName (HolyWeaponPut hw) = show hw
itemName (FillerPlacement f) = show f

-- XXX: We could automatically derive these from the definition of `Item`, but
-- it's a lot of complex type-level machinery for very little gain.
data ItemKind = ProgLvlCap | ProgWLv | HolyWeapon | FillerItem
  deriving (Show, Enum, Bounded, Typeable)

itemkind :: Item -> ItemKind
itemkind ProgressiveLevelCap = ProgLvlCap
itemkind (ProgressiveWLv _) = ProgWLv
itemkind (HolyWeaponPut _) = HolyWeapon
itemkind (FillerPlacement _) = FillerItem

progWLvName :: String
progWLvName = "weaponType"

holyWeaponKindName :: String
holyWeaponKindName = "holyWeapon"

fillerItemKindName :: String
fillerItemKindName = "fillerItem"

emitSetPayload :: (Monad m) => (String -> m ()) -> String -> Item -> m ()
emitSetPayload emitLn prefix item =
  case item of
    ProgressiveLevelCap -> return ()
    (ProgressiveWLv weapon) ->
      emitLn $ prefix ++ progWLvName ++ " = " ++ show weapon ++ ";"
    (HolyWeaponPut holyWeapon) ->
      emitLn $ prefix ++ holyWeaponKindName ++ " = " ++ show holyWeapon ++ ";"
    (FillerPlacement fillerItem) ->
      emitLn $ prefix ++ fillerItemKindName ++ " = " ++ show fillerItem ++ ";"

emitCPayloadUnion :: (Monad m) => (String -> m ()) -> m ()
emitCPayloadUnion emitLn = do
  emitLn $ "union Payload {"
  emitLn $ "  // progressive levelcap has no payload"
  emitLn $ "  enum " ++ show (typeRep @WeaponType) ++ " " ++ progWLvName ++ ";"
  emitLn $
    "  enum " ++ show (typeRep @HolyWeapon) ++ " " ++ holyWeaponKindName ++ ";"
  emitLn $
    "  enum " ++ show (typeRep @FillerItem) ++ " " ++ fillerItemKindName ++ ";"
  emitLn $ "};"

emitCEnum
  :: forall a
   . forall m
   . (Monad m, Bounded a, Enum a, Show a, Typeable a)
  => (String -> m ())
  -> m ()
emitCEnum emitLn = do
  emitLn $ "enum " ++ show (typeRep @a) ++ " {"
  forM_ [minBound @a .. maxBound] $ \v ->
    let name = show v
        i = show $ fromEnum v
     in emitLn $ "  " ++ name ++ "=" ++ i ++ ","
  emitLn "};"

headerLines :: [String]
headerLines =
  [ "THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY"
  , ""
  , "To change this file, see `bin/connector_config/Generate.hs` at"
  , "https://github.com/CT075/fe8-archipelago"
  ]

cCommentPrefix :: String
cCommentPrefix = "// "

pythonCommentPrefix :: String
pythonCommentPrefix = "# "

eventCommentPrefix :: String
eventCommentPrefix = "// "

emitHeader :: (Monad m) => String -> (String -> m ()) -> m ()
emitHeader commentPrefix emitLn =
  forM_ headerLines $ emitLn . (commentPrefix ++)

emitConnectorConfigH :: (Monad m) => (String -> m ()) -> m ()
emitConnectorConfigH emitLn = do
  emitHeader cCommentPrefix emitLn
  emitLn ""
  emitLn $ "#ifndef CONNECTOR_CONFIG_H"
  emitLn $ "#define CONNECTOR_CONFIG_H"
  emitLn ""
  emitLn $ "#include \"global.h\""
  emitLn ""
  emitCEnum @HolyWeapon emitLn
  emitLn ""
  emitLn "struct Checks {"
  emitLn $ "  u8 found[" ++ show locationBytes ++ "];"
  emitLn "};"
  emitLn ""
  emitLn $ "int chapterClearFlagIndex(int chapter);"
  emitLn $
    "int holyWeaponFlagIndex(enum " ++ show (typeRep @HolyWeapon) ++ " weapon);"
  emitLn ""
  -- CR-soon cam: change this to use allChapters
  forM_ [1 .. 20] $ \i -> do
    emitLn $ "#define Ch" ++ show i ++ "Id (" ++ show (fromEnum $ C i) ++ ")"
  emitLn $ "#define Ch5xId (" ++ show (fromEnum $ C5x) ++ ")"
  emitLn $ "#define PrologueId (" ++ show (fromEnum $ Prologue) ++ ")"
  emitLn $ "#define Endgame1Id (" ++ show (fromEnum $ Endgame1) ++ ")"
  emitLn $ "#define Endgame2Id (" ++ show (fromEnum $ Endgame2) ++ ")"
  forM_ [1 .. 8] $ \i ->
    emitLn $
      "#define Tower"
        ++ show i
        ++ "Id ("
        ++ show (fromEnum $ Tower i)
        ++ ")"
  forM_ [1 .. 10] $ \i ->
    emitLn $
      "#define Ruins"
        ++ show i
        ++ "Id ("
        ++ show (fromEnum $ Ruins i)
        ++ ")"
  emitLn ""
  emitCEnum @WeaponType emitLn
  emitLn ""
  emitCEnum @FillerItem emitLn
  emitLn ""
  emitLn $ "#define NUM_CHECKS (" ++ show numLocations ++ ")"
  emitLn ""
  emitCEnum @ItemKind emitLn
  emitLn ""
  emitCPayloadUnion emitLn
  emitLn ""
  emitLn $ "struct IncomingEvent {"
  emitLn $ "  enum " ++ show (typeRep @ItemKind) ++ " kind;"
  emitLn $ "  union Payload payload;"
  emitLn $ "};"
  emitLn ""
  emitLn $ "void unpackAPEventFromId(u16 id, struct IncomingEvent *dst);"
  emitLn ""
  emitLn $ "#endif // CONNECTOR_CONFIG_H"
  where
    locationBits = length $ [minBound @Location .. maxBound]
    locationBytesTrue = (locationBits + 7) `div` 8
    locationBytes = ((locationBytesTrue + 3) `div` 4) * 4

    numLocations = fromEnum (maxBound @Location) - fromEnum (minBound @Location) + 1

emitConnectorAccessorsC :: (Monad m) => (String -> m ()) -> m ()
emitConnectorAccessorsC emitLn = do
  emitHeader cCommentPrefix emitLn
  emitLn ""
  emitLn $ "#include \"connector_config.h\""
  emitLn ""
  emitLn $ "int chapterClearFlagIndex(int chapterId) {"
  emitLn $ "  return " ++ show (fromEnum $ ChapterClear Prologue) ++ "+chapterId;"
  emitLn $ "}"
  emitLn ""
  emitLn $
    "int holyWeaponFlagIndex(enum " ++ show (typeRep @HolyWeapon) ++ " weapon) {"
  emitLn $ "  switch (weapon) {"
  forM_ [minBound @HolyWeapon .. maxBound] $ \weapon -> do
    emitLn $ "    case " ++ show weapon ++ ":"
    emitLn $ "      return " ++ show (fromEnum (HolyWeaponGet weapon)) ++ ";"
  emitLn $ "    default:"
  emitLn $ "      return -1;"
  emitLn $ "  }"
  emitLn $ "}"
  emitLn ""
  emitLn $ "void unpackAPEventFromId(u16 id, struct IncomingEvent *dst) {"
  emitLn $ "  switch (id) {"
  forM_ [minBound @Item .. maxBound] $ \item -> do
    emitLn $ "    case " ++ show (fromEnum item) ++ ":"
    emitLn $ "      dst->kind = " ++ show (itemkind item) ++ ";"
    emitSetPayload emitLn "      dst->payload." item
    emitLn $ "      break;"
  emitLn $ "  };"
  emitLn $ "}"

emitPythonData :: (Monad m) => (String -> m ()) -> m ()
emitPythonData emitLn = do
  emitHeader pythonCommentPrefix emitLn
  emitLn ""
  emitLn "locations = ["
  forM_ [minBound @Chapter .. maxBound] $ emitLn . ("  " ++) . formatChapterClear
  forM_ [minBound @HolyWeapon .. maxBound] $ emitLn . ("  " ++) . formatHolyWeapon
  emitLn "]"
  emitLn ""
  emitLn "items = ["
  forM_ [minBound @Item .. maxBound] $ emitLn . ("  " ++) . formatItem
  emitLn "]"
  emitLn "SLOT_NAME_ADDR = {|archipelagoInfo|}"
  emitLn "SUPER_DEMON_KING_OFFS = {|ROM_BASE:archipelagoOptions|}"
  emitLn "LOCATION_INFO_OFFS = {|ROM_BASE:locItems|}"
  -- CR-someday cam: compute this from `sizeof(LocationItem)` instead of hardcoding
  emitLn "LOCATION_INFO_SIZE = 4"
  emitLn "ARCHIPELAGO_RECEIVED_ITEM_ADDR = {|receivedAPItem|}"
  emitLn "ARCHIPELAGO_NUM_RECEIVED_ITEMS_ADDR = {|receivedItemIndex|}"
  emitLn "FLAGS_ADDR = {|checkedLocations|}"
  emitLn $ "FLAGS_SIZE = " ++ show locationBytes
  where
    locationBits = length [minBound @Location .. maxBound]
    locationBytesTrue = (locationBits + 7) `div` 8
    locationBytes = ((locationBytesTrue + 3) `div` 4) * 4

    formatHolyWeapon weap =
      "("
        ++ show (holyWeaponLong weap)
        ++ ", "
        ++ show (fromEnum $ HolyWeaponGet weap)
        ++ "),"

    formatChapterClear c = "(" ++ formatChapterText c ++ ", " ++ show (fromEnum c) ++ "),"
      where
        formatChapterText Prologue = "\"Complete Prologue\""
        formatChapterText C5x = "\"Complete Chapter 5x\""
        formatChapterText (C i) =
          "\"Complete Chapter " ++ show i ++ "\""
        formatChapterText Endgame1 = "\"Defeat Lyon\""
        formatChapterText Endgame2 = "\"Defeat Formortiis\""
        formatChapterText (Tower i) =
          "\"Complete Tower of Valni " ++ show i ++ "\""
        formatChapterText (Ruins i) =
          "\"Complete Lagdou Ruins " ++ show i ++ "\""

    formatItem item = "(" ++ show (itemName item) ++ ", " ++ show (fromEnum item) ++ "),"

emitEventDefs :: (Monad m) => (String -> m ()) -> m ()
emitEventDefs emitLn = do
  emitHeader eventCommentPrefix emitLn
  emitLn ""
  forM_ [minBound @HolyWeapon .. maxBound] $ \hw ->
    emitLn $ "#define AP" ++ show hw ++ "Id " ++ show (fromEnum hw)

data GenOption
  = CLang
  | H
  | Py
  | Event

instance Read GenOption where
  readsPrec _ ('C' : rest) = [(CLang, rest)]
  readsPrec _ ('H' : rest) = [(H, rest)]
  readsPrec _ ('P' : 'y' : rest) = [(Py, rest)]
  readsPrec _ ('E' : 'v' : 'e' : 'n' : 't' : rest) = [(Event, rest)]
  readsPrec _ _ = []

usage :: String
usage = "usage: ./Generate [C/H/Py/Event]"

main :: IO ()
main = do
  args <- getArgs
  firstArg <-
    case args of
      [x] -> return x
      _ -> printUsage
  case readMaybe @GenOption firstArg of
    Just CLang -> emitConnectorAccessorsC putStrLn
    Just H -> emitConnectorConfigH putStrLn
    Just Py -> emitPythonData putStrLn
    Just Event -> emitEventDefs putStrLn
    Nothing -> printUsage
  where
    exitUsage = ExitFailure 64
    printUsage = do
      hPutStrLn stderr usage
      exitWith exitUsage
