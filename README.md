# Minesweeper

A minesweeper game to showcase a glimpse of the tool/ UI capabilities of the author.

## What's included?
- An editor toolbar button to show the minesweeper window. Located besides the `Platform` combo box at the top of the window.
- A completely working minesweeper game with a win and lose condition and a modifiable input for its width, height, and the mine count. You can always restart the game.
- Some input validations.
- An editor exposed properties to modify the minesweeper display settings (Cell size, padding, etc). Located at the `Project Settings`. Default ini file is saved on the plugin configs but can always be overriden by each project.
- A responsive UI to meet minimum requirements.

## What can be improved?
- Add more input validation like having max cell counts to avoid overwhelming the screen.
- Improve overall UI (fonts, sizing, etc)
- Consider reusing the existing board, instead of re-creating everytime a new game starts.
- Improve the cell UI class to state-based instead of event-based (SetReveal(true) vs Reveal()). Useful especially if the board is just being reused.

## Additional Notes
- Created two modules. For Core and Editor codes. The idea is you can also use the minesweeper code (even the UI) on a game runtime environment. The minesweeper functionality is decoupled from any UI code.
- Only the toolbar icon (svg) and the minesweeper logic is assisted by AI to focus more on the UI programming and general structure of the system. It was provided as a native C++ class by the AI, and I removed the `std::cin`/ `std::cout`, then translated it to a more UE-friendly code (`std::vector` to `TArray`, added delegates, etc), and add more validations including the win codition.
- Created in around 4 hours from setup up to creating this readme file.
