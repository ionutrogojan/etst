#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINK_LENGTH 2000
#define MAX_PATH_LENGTH 4096

int openLink(const char* link) {
	// xdg-open + https://www... + > /dev/null 2>&1 + spaces & '\0'
	// 8 + 2000 + 16 + 3 (rounded to 2048)
	char cmd[2048];
	int fmtRet = 0;
#ifdef __linux__ // LINUX
	fmtRet = sprintf(cmd, "xdg-open '%s' > /dev/null 2>&1", link);
#elif __APPLE__ // MACOS
	fmtRet = sprintf(cmd, "open '%s'", link);
#elif _WIN32 // WINDOWS
	fmtRet = sprintf(cmd, "explorer '%s'", link);
#endif
	if (fmtRet < 0 || fmtRet > sizeof(cmd)) {
		printf("  [ERROR] Unable to format 'openLink' command\n");
		return fmtRet;
	}
	int ret = system(cmd);
	return ret;
}

int main(void) {
	FILE* file = NULL;
	char line[MAX_LINK_LENGTH];
	char configPath[MAX_PATH_LENGTH]; // Linux MAX_PATH_LENGTH is 4096 chars / bytes

	const char* homeDir = getenv("HOME");

	if (homeDir != NULL) {
		// TODO: find a way to format the path better
		// homeDir + /.config/webbox/ + configFile
		int fmtRet = sprintf(configPath, "%s/.config/webbox/default.cfg", homeDir);
		if (fmtRet < 0 || fmtRet > sizeof(configPath)) {
			printf("  [ERROR] Unable to format 'configPath'\n");
			return 1;
		}
	}

	if ((file = fopen(configPath, "r")) == NULL) {
		printf("  [ERROR] Unable to read '%s'\n", configPath);
		return 1;
	}
	
	while (fgets(line, sizeof(line), file) != NULL) {
		switch (line[0]) {
			case '\n':
				goto funcEnd;
			case '#':
			case ';':
				continue;
			default:
				if (line[strlen(line) - 1] == '\n') {
					line[strlen(line) - 1] = '\0';
				}
				switch (openLink(line)) {
					case 0:
						printf("[SUCCESS]");
						break;
					default:
						printf("  [ERROR]");
						break;
				}
				printf(" %s\n", line);
			break;
		}
	}
funcEnd:
	fclose(file);
	return 0;
}

// TODO: add section support for setup, links and more