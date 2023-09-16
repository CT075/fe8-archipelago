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
    , 0x24 -- Orson
    , 0x25 -- Glen
    , 0x26 -- Selena
    , 0x27 -- Valter
    , 0x28 -- Riev
    , 0x29 -- Caellach
    , 0x2A -- Fado
    , 0x40 -- Lyon (Ch 17)
    , 0x41 -- Morva (Ch 20)
    , 0x42 -- Orson (Ch 5x)
    , 0x43 -- Valter (Ch 15)
    , 0x44 -- Selena (Ch 10B & 13B)
    , 0x45 -- Valter (Prologue)
    , 0x46 -- Breguet (Ch 1)
    , 0x47 -- Bone (Ch 2)
    , 0x48 -- Bazba (Ch 3)
    , 0x49 -- Entombed (Ch 4)
    , 0x4A -- Saar (Ch 5)
    , 0x4B -- Novala (Ch 6)
    , 0x4C -- Murray (Ch 7)
    , 0x4D -- Tirado (Ch 8)
    , 0x4E -- Binks (Ch 9A)
    , 0x4F -- Pablo (Ch 10A)
    , 0x50 -- Maelduin (Ch 12A)
    , 0x51 -- Aias (Ch 13A)
    , 0x52 -- Carlyle (Ch 14A)
    , 0x53 -- Caellach (Ch 15)
    , 0x54 -- Pablo (Ch 13A)
    , 0x56 -- Gorgon (Ch 18)
    , 0x57 -- Riev (Ch 19 & 20)
    , 0x5A -- Gheb (Ch 9B)
    , 0x5B -- Beran (Ch 10B)
    , 0x5C -- Cyclops (Ch 12B)
    , 0x5D -- Wight (Ch 11A)
    , 0x5E -- Deathgoyle (Ch 11B)
    , 0x68 -- O'Neill (Prologue)
    , 0x6A -- Zonta (Ch 5x)
    , 0x6B -- Vigarde (Ch 14B)
    , 0x6C -- Lyon (Ch Final)
    , 0x6D -- Orson (Ch 16)
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
