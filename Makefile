CONTAINER=qt_discovery
EXECUTABLE=HelloQt


.PHONY: all install container project run run42 rmcontainer rmproject rm re redeploy redeploy42

all: container project run42

install-qt:
	@sudo apt update
	@sudo apt install qt6-base-dev qt6-base-dev-tools libgl1-mesa-dev libopengl-dev
	@sudo apt install libxcb-xinerama0
	@echo "QT installed on on host"

container:
	@docker build -t $(CONTAINER) .
	@echo "Container $(CONTAINER) built"

project:
	@docker run --rm -e DISPLAY="$$DISPLAY" -v "$$(pwd)":/workspace $(CONTAINER) cmake -S . -B build -G Ninja
	@docker run --rm -e DISPLAY="$$DISPLAY" -v "$$(pwd)":/workspace $(CONTAINER) cmake --build build
	@echo "Project $(EXECUTABLE) built"

run:
	@./build/$(EXECUTABLE)
	@echo "Project $(EXECUTABLE) run"

run42:
	@echo "Project $(EXECUTABLE) run"
	@xhost +local:docker
	@docker run --rm -e DISPLAY="$$DISPLAY" -e XDG_RUNTIME_DIR="$$XDG_RUNTIME_DIR" \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		-v "$$(pwd)":/workspace \
		--device /dev/dri \
		qt_discovery ./build/HelloQt

rmcontainer:
	@docker rmi $(CONTAINER)
	@echo "Container $(CONTAINER) removed"
rmproject:
	@echo "Project $(EXECUTABLE) removed"

rm: rmcontainer rmproject

re: rm all

redeploy: project run
redeploy42: project run42
