SRC_DIR := Server
COMMON_DIR :=NetUtils

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp) 
COMMON_FILES := $(wildcard $(COMMON_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(SRC_FILES)) $(patsubst $(COMMON_DIR)/%.cpp,$(COMMON_DIR)/%.o,$(COMMON_FILES))

LDFLAGS := -lpthread
EXEC_FILE := Game_server.out

$(EXEC_FILE): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(OBJ_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC_FILE) $(OBJ_FILES)