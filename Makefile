export INCLUDES= -I/usr/local/include/opencv -I/usr/local/include/opencv2
export LINKS=-lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
export LIBRARIES=-L/usr/local/lib/ $(LINKS)
export BINARY=main
export FLAGS= -O3 -Wall -g

$@.cpp:
	g++ $(FLAGS) $@.cpp $(INCLUDES) $(LIBRARIES) -o $(BINARY)

