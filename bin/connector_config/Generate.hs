{-# LANGUAGE AllowAmbiguousTypes #-}
{-# LANGUAGE KindSignatures #-}
{-# LANGUAGE RankNTypes #-}
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

-- TODO: Python gen

import Control.Arrow
import Control.Monad
import Data.Char
import Data.Void
import Type.Reflection

-- Datatypes
--
-- Because we want a nice, uniform representation on the GBA side, we define a
-- server event to be a `(Kind, Payload)` pairing, which has a simple and
-- obvious representation as a pair of fixed-width integers.
--
-- CR cam: Doing this with Haskell-level types instead of just lists of strings
-- is _way_ overengineering things.

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
    deriving (Show, Enum, Bounded, Typeable)

data WeaponKind = Sword | Lance | Axe | Bow | Anima | Light | Dark | Staff
    deriving (Show, Enum, Bounded, Typeable)

data OutgoingEventKind where
    GotHolyWeapon :: OutgoingEventKind -- HolyWeapon
    ClearedChapter :: OutgoingEventKind -- Int
    deriving (Show, Enum, Bounded, Typeable)

data IncomingEventKind where
    ProgressiveLevelCap :: IncomingEventKind -- Void
    ProgressiveWeaponLevelCap :: IncomingEventKind -- WeaponKind
    GetItem :: IncomingEventKind -- Int
    deriving (Show, Enum, Bounded, Typeable)

data U8

-- Code generation

class CTypeManifest ty where
    withCTypeManifest :: Monad m => (String -> m ()) -> m ()

instance {-# OVERLAPS #-} (Enum a, Bounded a, Typeable a) => CTypeManifest a where
    withCTypeManifest = ($ "enum " ++ show (typeRep @a))

instance CTypeManifest U8 where
    withCTypeManifest = ($ "u8")

instance CTypeManifest Void where
    withCTypeManifest _ = return ()

class Typeable a => EnumGen a where
    variants :: [(String, Int)]

    emitCEnum :: Monad m => (String -> m ()) -> m ()
    emitCEnum emitln = do
        emitln $ "enum " ++ show (typeRep @a) ++ " {"
        forM_ (variants @a) $ \(name, variant) ->
            emitln ("  " ++ name ++ "=" ++ show variant ++ ",")
        emitln "};"

instance (Show a, Enum a, Bounded a, Typeable a) => EnumGen a where
    -- CR cam: These generate NONSPACED names; it'd be cool if we could process
    -- these to be UNDERSCORE_SPACED instead.
    variants = map ((map toUpper . show) &&& fromEnum) (enumFrom (toEnum @a 0))

class (Enum a, Bounded a) => UnionGen a where
    unionName :: String
    withVariantData :: Monad m => ((String, String) -> m ()) -> a -> m ()

-- CR cam: It'd be nice to unify all these near-identical clauses somehow
instance UnionGen OutgoingEventKind where
    unionName = "OutgoingPayload"

    withVariantData f GotHolyWeapon = withCTypeManifest @HolyWeapon (\s -> f (s, "holyWeaponID"))
    withVariantData f ClearedChapter = withCTypeManifest @U8 (\s -> f (s, "chapterID"))

instance UnionGen IncomingEventKind where
    unionName = "IncomingPayload"

    withVariantData f ProgressiveLevelCap = withCTypeManifest @Void (\s -> f (s, "levelcap"))
    withVariantData f ProgressiveWeaponLevelCap =
        withCTypeManifest @WeaponKind (\s -> f (s, "weaponKind"))
    withVariantData f GetItem = withCTypeManifest @U8 (\s -> f (s, "itemID"))

emitCUnion :: forall a. forall m. (UnionGen a, Monad m) => (String -> m ()) -> m ()
emitCUnion emitLn = do
    emitLn $ "union " ++ unionName @a ++ " {"
    let emitUnionField (ty, name) = emitLn $ "  " ++ ty ++ " " ++ name ++ ";"
    forM_ (enumFrom (toEnum 0)) $ withVariantData @a emitUnionField
    emitLn $ "};"

emitCEventStruct :: Monad m => String -> (String -> m ()) -> m ()
emitCEventStruct prefix emitLn = do
    emitLn $ "struct " ++ prefix ++ "Event {"
    emitLn $ "  enum " ++ prefix ++ "EventKind kind;"
    emitLn $ "  union " ++ prefix ++ "Payload payload;"
    emitLn $ "  bool seen;"
    emitLn $ "};"

pythonCommentPrefix = "# "
cCommentPrefix = "// "

headerLines =
    [ "THIS FILE IS GENERATED, DO NOT EDIT DIRECTLY"
    , ""
    , "To change this file, see `bin/connector_config/Generate.hs` at"
    , "https://github.com/CT075/fe8-archipelago"
    , ""
    ]

-- TODO: extract common structure out between python/c

generateCHeader :: Monad m => (String -> m ()) -> m ()
generateCHeader emitLn = do
    -- Generate header
    forM_ headerLines (emitLn . (cCommentPrefix ++))
    emitLn ""

    -- Generate payload content enums
    --
    -- CR cam: After everything, we have no way of enforcing that we emit all
    -- of the enums that we need to...
    emitCEnum @HolyWeapon emitLn
    emitLn ""
    emitCEnum @WeaponKind emitLn
    emitLn ""

    -- Generate payload shape unions
    emitCUnion @IncomingEventKind emitLn
    emitLn ""
    emitCUnion @OutgoingEventKind emitLn
    emitLn ""

    -- Generate event kind enums
    emitCEnum @IncomingEventKind emitLn
    emitLn ""
    emitCEnum @OutgoingEventKind emitLn
    emitLn ""

    -- Generate struct types
    emitCEventStruct "Out" emitLn
    emitLn ""
    emitCEventStruct "In" emitLn
    emitLn ""

-- Generate event structs

main :: IO ()
main = do
    generateCHeader putStrLn
