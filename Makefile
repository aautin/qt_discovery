CONTAINER=qt_discovery
EXECUTABLE=HelloQt


.PHONY: all install container project run rmcontainer rmproject rm re redeploy

all: container project run

install-qt:
	sudo apt update
	sudo apt install qt6-base-dev qt6-base-dev-tools libgl1-mesa-dev libopengl-dev
	sudo apt install libxcb-xinerama0

container:
	docker build -t $(CONTAINER) .

project:
	docker run --rm -e DISPLAY=$$(DISPLAY) -v "$$(pwd)":/workspace $(CONTAINER) cmake -S . -B build -G Ninja
	docker run --rm -e DISPLAY=$$(DISPLAY) -v "$$(pwd)":/workspace $(CONTAINER) cmake --build build

run:
	./build/$(EXECUTABLE)

rmcontainer:
	docker rmi $(CONTAINER)

rmproject:
	sudo rm -rf build

rm: rmcontainer rmproject

re: rm all
redeploy: project run
