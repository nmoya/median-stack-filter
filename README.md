# Install opencv2

```
brew update
brew tap homebrew/science
brew install opencv
```

# Link opencv2 to python
```
cd /Library/Python/2.7/site-packages/
sudo ln -s /usr/local/Cellar/opencv/2.4.9/lib/python2.7/site-packages/cv.py cv.py
sudo ln -s /usr/local/Cellar/opencv/2.4.9/lib/python2.7/site-packages/cv2.so cv2.so
```

# Install opencv3
```
brew install opencv3 --with-contrib
```