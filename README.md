Project implements a basic realtime lane and vehicle tracking using OpenCV and focused in the computer vision aspect of it, a crucial module. If an automated car is going to drive around unpredictable environments, it has to be able to perceive and detect every small detail that surrounds it.
So for this project, a lane detection algorithm is proposed as part of the perception component for a self driving vehicle. By using a video feed input of a car driving on the highway, the algorithm will detect where the lane is so that the car can use its location to avoid getting out of the it. 
It will also be able to predict any turn on the road to secure a good tracking of the lane. The project was developed using C++, CMake and the OpenCV library. 
The input video was taken from Self-Driving Car.

![ArezouSohrabvand_Lanefinder3](https://user-images.githubusercontent.com/71450268/105053551-12378500-5a3f-11eb-9de5-84c648941054.png)

![ArezouSohrabvand_Lanefinder3-1](https://user-images.githubusercontent.com/71450268/105053559-14014880-5a3f-11eb-9676-21abd895847e.png)

Implemented with:

OpenCV 2

C/C++ using Microsoft Visual Studio 2019 IDE.


OpenCV features used & used techniques:

Gaussian smoothing for image noise removal

Canny edge detection 

Hough transform for line detection

Haar features for vehicle detection (hypothesis generation) 

Vehicle hypothesis verification using horizontal edges and symmetry 
