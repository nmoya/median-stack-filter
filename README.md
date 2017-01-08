# Installation

## Install g++
Install gcc on your machine. Example:
`brew install [flags] gcc48`

## Install opencv2

```
brew update
brew tap homebrew/science
brew install opencv
```

# Usage

- Go to the project folder
- Compile: `make main`
- Run: `./main <images folder>`.

Example:
`./main database/ams`

This will load all images inside the `database/ams` folder and apply the median stack filter. A window will be displayed with the result.

The code is prepared for color images, but its main function can be easialy modified to work with grayscale images.