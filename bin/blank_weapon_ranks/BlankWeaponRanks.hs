{-# OPTIONS_GHC -Werror=incomplete-patterns #-}

import Control.Monad (forM_)

playerIds :: [Int]
playerIds =
    [ 0x01 -- Eirika
    , 0x02 -- Seth
    , 0x03 -- Gilliam
    , 0x04 -- Frantz
    , 0x05 -- Moulder
    , 0x06 -- Vanessa
    , 0x07 -- Ross
    , 0x08 -- Neimi
    , 0x09 -- Colm
    , 0x0A -- Garcia
    , 0x0B -- Innes
    , 0x0C -- Lute
    , 0x0D -- Natasha
    , 0x0E -- Cougar
    , 0x0F -- Ephraim
    , 0x10 -- Forde
    , 0x11 -- Kyle
    , 0x12 -- Amelia
    , 0x13 -- Artur
    , 0x14 -- Gerik
    , 0x15 -- Tethys
    , 0x16 -- Marisa
    , 0x17 -- Saleh
    , 0x18 -- Ewan
    , 0x19 -- L'Arachel
    , 0x1A -- Dozla
    , 0x1C -- Rennac
    , 0x1D -- Duessel
    , 0x1E -- Myrrh
    , 0x1F -- Knoll
    , 0x20 -- Joshua
    , 0x21 -- Syrene
    , 0x22 -- Tana
    , 0x23 -- Lyon
    , 0x42 -- Orson
    ]

blankWeaponRankForUnit :: Int -> [String]
blankWeaponRankForUnit unitId =
    [ "ORG 0x803D30+(" ++ show unitId ++ "*52)+20"
    , "BYTE 0 0 0 0 0 0 0 0"
    , ""
    ]

main :: IO ()
main = do
    putStrLn "PUSH"
    putStrLn ""
    forM_ playerIds $ flip forM_ putStrLn . blankWeaponRankForUnit
    putStrLn "POP"
