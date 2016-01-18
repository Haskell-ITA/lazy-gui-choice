
-- | This is a first attempt using an imperative-like approach, and using wxhaskell library.
--
--   TODO total effort is not dynamically/incrementally updated
--   TODO there is no yet explicit/separated model
--   TODO the model should update total effort incrementally

module Main where

import Graphics.UI.WX
import Graphics.UI.WXCore

main :: IO ()
main = run gui

gui :: IO ()
gui = do
    f <- frame [text := "lazy-gui-choice"]
    p <- panel f []
    totalEffort <- staticText p []
    estimatedEffort <- staticText p []
    g <- gridCtrl p []
    gridAddTheRows g modelData
    gridAutoSize g
    let (totalEffortVal, estimatedEffortVal) = calculateEfforts modelData
    set totalEffort [text := ("Total effort: " ++ show totalEffortVal)]
    set estimatedEffort [text := ("Estimated effort: " ++ show estimatedEffortVal)]
    
    -- Layout
    set f [layout := container p $ margin 5 $ column 5 [shaped $ widget totalEffort, shaped $ widget estimatedEffort, shaped $ dynamic $ widget g]]
    set f [visible := True]
    return ()


modelData = [("Pranzare", 20, False)
            ,("Conquistare il mondo", 100, True)
            ]

calculateEfforts = foldr (\(_, time, done) (total, estimated) -> (if done then total + time else total, estimated + time)) (0, 0)

gridCtrl :: Window a -> [Prop (Grid ())] -> IO (Grid ())
gridCtrl parent props = feed2 props 0 $
    initialWindow $ \i rect props style -> do
        g <- gridCreate parent i rect 0
        gridCreateGrid g 0 3 0
        gridSetColLabelValue g 0 "Name"
        gridSetColLabelValue g 1 "Estimate/Effort"
        gridSetColLabelValue g 2 "Done"
        gridSetRowLabelSize g 0 -- Don't show row labels
        return g


gridAddTheRows g xs = do
    n <- gridGetNumberRows g
    gridAddRows g n xs

gridAddRows g initialRow [] = return g
gridAddRows g initialRow ((name, estimate, done):xs) = do
    gridAppendRows g 1 True
    gridSetCellValue g initialRow 0 name
    gridSetCellValue g initialRow 1 (show estimate)
    gridSetCellValue g initialRow 2 (show done)
    gridAddRows g (initialRow + 1) xs

