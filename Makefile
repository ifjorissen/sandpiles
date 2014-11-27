# Isabella Jorissen
# Hw. 6
# Math 389
# 11.27.14

M4 := $(shell which m4)
LOC := ~/Desktop/math389/hw/hw6
# DEPS := m4/base.m4
# ifneq ($(shell test -f overrides.m4 || echo n),n)
# 	DEPS += overrides.m4
# endif

#user_env : $(shell basename ${VIRTUAL_ENV})

# .PHONY: all init settings clean run help
	
all: compile renderOpenGL renderASCII

compile:
	gcc -pthread -o renderOpenGL render_piles.c sandgrid.c barrier.c -framework OpenGL -framework GLUT
	gcc -pthread -o renderASCII sandpile.c sandgrid.c barrier.c

renderOpenGL:
	$(eval activate_term := 'tell application "Terminal" to activate')
	$(eval open_tab := 'tell application "System Events" to tell process "Terminal" to keystroke "t" using command down')
	$(eval start_env := 'tell application "Terminal" to do script "cd $(LOC) && ./renderOpenGL" in selected tab of the front window')
	osascript -e ${activate_term} -e ${open_tab} -e ${start_env}

renderASCII:
	$(eval activate_term := 'tell application "Terminal" to activate')
	$(eval open_tab := 'tell application "System Events" to tell process "Terminal" to keystroke "t" using command down')
	$(eval start_env := 'tell application "Terminal" to do script "cd $(LOC) && ./renderASCII" in selected tab of the front window')
	osascript -e ${activate_term} -e ${open_tab} -e ${start_env}




help:
	@echo "Please use \`make <target>' where <target> is one of"
	@echo "  all           to make IT ALL"
	@echo "  help          :)"
