export LIB_DIR=./lib
export LIBRARIES= -L$(LIB_DIR) -L/usr/local/lib/
export INCLUDE_DIR=./headers
export INCLUDES= -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I$(INCLUDE_DIR)
# export INCLUDES_OPENCV3=-I/usr/local/opt/opencv3/include
export LINKS=-lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
# export LINKS_OPENCV3=-L/usr/local/opt/opencv3/lib
export SRC_DIR=./src
export OBJ_DIR=./obj
export BINARY=bokeh

# Quick test in main
# g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -O3 -Wall -g main.cpp -o main && ./main salt.png

# Quick test in main with google test library
# g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/gtest -lgtest -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -O3 -Wall -g main.cpp -o main && ./main salt.png


# Flags. Debug or Otimized
#export FLAGS= -ggdb -O0 -Wall -D _DEBUG
#g++ $(FLAGS) $(INCLUDES) $(LIBRARIES) -o $(BINARY) Circle.cpp Line.cpp ObjectClassifier.cpp Objects.cpp Rectangle.cpp main.cpp $(LINKS)
export FLAGS= -O3 -Wall -g

SOURCES=$(shell ls $(SRC_DIR))


all: libbokeh
	@echo "ocv.a created..."
	@echo "DONE."

libbokeh:
	@echo "Build process started...";
	$(foreach source, $(SOURCES), g++ $(FLAGS) -c $(SRC_DIR)/$(source) $(INCLUDES) -o $(OBJ_DIR)/$(subst .cpp,,$(source)).o;)

	@echo "";
	ar csr $(LIB_DIR)/libbokeh.a \
	$(foreach source, $(SOURCES), $(OBJ_DIR)/$(subst .cpp,,$(source)).o)

	@echo "";


$@.cpp: libbokeh $@.cpp
	make libbokeh
	g++ $(FLAGS) $@.cpp $(INCLUDES) $(LIBRARIES) -lbokeh $(LINKS) -o $(BINARY)

clean:
	rm -f $(BINARY)
	rm -rf $(BINARY).dSYM
	rm $(OBJ_DIR)/*
	rm $(LIB_DIR)/*

