{-# LANGUAGE AllowAmbiguousTypes #-}
{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE TypeApplications #-}
{-# OPTIONS_GHC -Werror=incomplete-patterns #-}

-- The main purpose of this file is to generate both the necessary C header
-- (for building the ROM) and a python module defining the relevant types (for
-- the client to communicate with the ROM).
--
-- By generating both files from a common source, we can ensure that they never
-- drift out of sync, and also means that this file can serve as a single point
-- of reference for such events.

import Control.Monad (forM_)
import Data.List
import System.Environment (getArgs)
import System.Exit (ExitCode (..), exitWith)
import System.IO (hPutStrLn, stderr)
import Text.Read (readMaybe)
import Type.Reflection

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
  deriving (Show, Enum, Bounded, Typeable, Eq)

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
  deriving (Show, Enum, Bounded, Typeable, Eq)

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
  deriving (Show, Typeable)

instance Bounded Location where
  minBound = ChapterClear minBound
  maxBound = HolyWeaponGet maxBound

instance Enum Location where
  toEnum i
    | i < 0 = error $ "invalid location index " ++ show i
    | i <= fromEnum (maxBound @Chapter) = ChapterClear $ toEnum i
    | otherwise = HolyWeaponGet $ toEnum $ i - fromEnum (maxBound @Chapter) - 1

  fromEnum (ChapterClear c) = fromEnum c
  fromEnum (HolyWeaponGet hw) = fromEnum hw + fromEnum (maxBound @Chapter) + 1

data WeaponType
  = Sword
  | Lance
  | Axe
  | Bow
  | Staff
  | Anima
  | Light
  | Dark
  deriving (Show, Enum, Bounded, Typeable, Eq)

data Item
  = ProgressiveLevelCap
  | ProgressiveWLv WeaponType
  | HolyWeaponPut HolyWeapon
  | FillerPlacement FillerItem
  deriving (Show, Typeable)

instance Bounded Item where
  minBound = ProgressiveLevelCap
  maxBound = FillerPlacement maxBound

-- CR-someday cam: we should be able to generate this
instance Enum Item where
  succ ProgressiveLevelCap = ProgressiveWLv $ minBound @WeaponType
  succ (ProgressiveWLv wt) =
    if wt == maxBound @WeaponType
      then HolyWeaponPut $ minBound @HolyWeapon
      else ProgressiveWLv $ succ wt
  succ (HolyWeaponPut hw) =
    if hw == maxBound @HolyWeapon
      then FillerPlacement $ minBound @FillerItem
      else HolyWeaponPut $ succ hw
  succ (FillerPlacement fp) =
    if fp == maxBound @FillerItem
      then error $ "called [Item::succ] on [Item::maxBound]"
      else FillerPlacement $ succ fp

  pred ProgressiveLevelCap = error $ "called [Item::pred] on [Item::minBound]"
  pred (ProgressiveWLv wt) =
    if wt == minBound @WeaponType
      then ProgressiveLevelCap
      else ProgressiveWLv $ pred wt
  pred (HolyWeaponPut hw) =
    if hw == minBound @HolyWeapon
      then ProgressiveWLv $ maxBound @WeaponType
      else HolyWeaponPut $ pred hw
  pred (FillerPlacement fp) =
    if fp == minBound @FillerItem
      then HolyWeaponPut $ maxBound @HolyWeapon
      else FillerPlacement $ pred fp

  toEnum 0 = ProgressiveLevelCap
  toEnum i =
    if i < 0
      then error $ "called [Item::toEnum] on negative number"
      else succ $ toEnum (i - 1)

  fromEnum ProgressiveLevelCap = 0
  fromEnum t = fromEnum (pred t) + 1

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
