# SMART-Data-Vis-v1

Updated version of: https://github.com/StudentMobileApp/SMART-Data-Visualization-Release-Versions

May 1, 2020:

Changes:

1. Added ability to show or not show a class (This uses the dropdown list the class colors was already using)
2. You now have to choose a graph before one shows up
3. The number of linked graphs in the STS-SPC will now reset when loading a new graph
4. Minor UI and code adjustments

Personal Goals:

1. A reset button if separated graphs were moved
2. Mouse shows point/vector info?

Personal Note: OpenMP/threading is problematic as openGL is not thread safe and the vector class is being used sequentially (i.e. vectorname.puck_back(x)).


