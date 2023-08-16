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
    deriving (Show, Enum, Bounded, Typeable)

holyWeaponShort :: HolyWeapon -> String
holyWeaponShort = show @HolyWeapon

holyWeaponLong :: HolyWeapon -> String
holyWeaponLong = (++ " Received") . show @HolyWeapon

data Chapter
    = Prologue
    | -- For now, we treat Eirika and Ephraim versions of the same map as the
      -- same location
      C Int
    | C5x
    | Endgame
    | Victory
    deriving (Show, Typeable)

instance Bounded Chapter where
    minBound = Prologue
    maxBound = Endgame

instance Enum Chapter where
    toEnum 0 = Prologue
    toEnum 6 = C5x
    toEnum 22 = Endgame
    toEnum 23 = Victory
    toEnum i
        | i < 1 = error $ "invalid chapter index " ++ show i
        | i < 6 = C i
        | i < 22 = C (i - 1)
        | otherwise = error $ "invalid chapter index " ++ show i

    fromEnum Prologue = 0
    fromEnum C5x = 6
    fromEnum Endgame = 22
    fromEnum Victory = 23
    fromEnum (C i)
        | i < 6 = i
        | otherwise = i + 1

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

emitCEnum ::
    forall a.
    forall m.
    (Monad m, Bounded a, Enum a, Show a, Typeable a) =>
    (String -> m ()) ->
    m ()
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

emitHeader :: Monad m => String -> (String -> m ()) -> m ()
emitHeader commentPrefix emitLn =
    forM_ headerLines $ emitLn . (commentPrefix ++)

emitConnectorConfigH :: Monad m => (String -> m ()) -> m ()
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
    emitLn $ "int holyWeaponFlagIndex(enum " ++ show (typeRep @HolyWeapon) ++ " weapon);"
    emitLn ""
    forM_ [1 .. 20] $ \i -> do
        emitLn $ "#define Ch" ++ show i ++ "Id (" ++ show (fromEnum $ C i) ++ ")"
    emitLn $ "#define Ch5xId (" ++ show (fromEnum $ C5x) ++ ")"
    emitLn $ "#define PrologueId (" ++ show (fromEnum $ Prologue) ++ ")"
    emitLn $ "#define EndgameId (" ++ show (fromEnum $ Endgame) ++ ")"
    emitLn ""
    emitLn $ "const u16 *receivedItemEvent(u8 itemId);"
    emitLn ""
    emitLn $ "#endif // CONNECTOR_CONFIG_H"
  where
    locationBits = length $ [minBound @Location .. maxBound]
    locationBytesTrue = (locationBits + 7) `div` 8
    locationBytes = ((locationBytesTrue + 3) `div` 4) * 4

emitConnectorAccessorsC :: Monad m => (String -> m ()) -> m ()
emitConnectorAccessorsC emitLn = do
    emitHeader cCommentPrefix emitLn
    emitLn ""
    emitLn $ "#include \"connector_config.h\""
    emitLn ""
    emitLn $ "int chapterClearFlagIndex(int chapterId) {"
    emitLn $ "  return " ++ (show $ fromEnum $ ChapterClear Prologue) ++ "+chapterId;"
    emitLn $ "}"
    emitLn ""
    emitLn $ "int holyWeaponFlagIndex(enum " ++ show (typeRep @HolyWeapon) ++ " weapon) {"
    emitLn $ "  switch (weapon) {"
    forM_ [minBound @HolyWeapon .. maxBound] $ \weapon -> do
        emitLn $ "    case " ++ show weapon ++ ":"
        emitLn $ "      return " ++ show (fromEnum (HolyWeaponGet weapon)) ++ ";"
    emitLn $ "    default:"
    emitLn $ "      return -1;"
    emitLn $ "  }"
    emitLn $ "}"

emitPythonLocations :: Monad m => (String -> m ()) -> m ()
emitPythonLocations emitLn = do
    emitHeader pythonCommentPrefix emitLn
    emitLn ""
    emitLn "locations = ["
    forM_ [minBound @Chapter .. maxBound] $ emitLn . ("  " ++) . formatChapterClear
    forM_ [minBound @HolyWeapon .. maxBound] $ emitLn . ("  " ++) . formatHolyWeapon
    emitLn "]"
  where
    formatHolyWeapon weap =
        "("
            -- ++ show (holyWeaponShort weap)
            -- ++ ", "
            ++ show (holyWeaponLong weap)
            ++ ", "
            ++ show (fromEnum $ HolyWeaponGet weap)
            ++ "),"

    formatChapterClear c = "(" ++ formatChapterText c ++ ", " ++ (show $ fromEnum c) ++ "),"
      where
        formatChapterText Prologue = "\"Complete Prologue\""
        formatChapterText C5x = "\"Complete Chapter 5x\""
        formatChapterText (C i) =
            "\"Complete Chapter " ++ show i ++ "\""
        formatChapterText Endgame = "\"Defeat Lyon\""
        formatChapterText Victory = "\"Defeat Formortiis\""

data GenOption
    = CLang
    | H
    | Py

instance Read GenOption where
    readsPrec _ ('C' : rest) = [(CLang, rest)]
    readsPrec _ ('H' : rest) = [(H, rest)]
    readsPrec _ ('P' : 'y' : rest) = [(Py, rest)]
    readsPrec _ _ = []

usage :: String
usage = "usage: ./Generate [C/H/Py]"

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
        Just Py -> emitPythonLocations putStrLn
        Nothing -> printUsage
  where
    exitUsage = ExitFailure 64
    printUsage = do
        hPutStrLn stderr usage
        exitWith exitUsage
