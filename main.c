#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINK_LENGTH 2000

#ifdef __linux__ // LINUX
	#define MAX_PATH_LENGTH 4096
#elif __APPLE__ // MACOS
	#define MAX_PATH_LENGTH 256
#elif _WIN32 // WINDOWS
	#define MAX_PATH_LENGTH 260
#endif

int openLink(const char *link) {
	// xdg-open + https://www... + > /dev/null 2>&1 + spaces & '\0'
	// 8 + 2000 + 16 + 3 (rounded to 2048)
	char cmd[MAX_LINK_LENGTH + 48];
	int fmtRet = 0;
#ifdef __linux__ // LINUX
	fmtRet = snprintf(cmd, sizeof(cmd), "xdg-open '%s' > /dev/null 2>&1", link);
#elif __APPLE__ // MACOS
	fmtRet = snprintf(cmd, sizeof(cmd), "open '%s'", link);
#elif _WIN32 // WINDOWS
	fmtRet = snprintf(cmd, sizeof(cmd), "explorer '%s'", link);
#endif
	if (fmtRet < 0 || fmtRet > sizeof(cmd)) {
		printf("  [ERROR] Unable to format 'openLink' command\n");
		return fmtRet;
	}
	int ret = system(cmd);
	return ret;
}

const char *getConfigDirectory(void) {

#ifdef _WIN32 // WINDOWS
	const char *appData = getenv("APPDATA");
	if (appData == NULL)
		return NULL; // Error: APPDATA environment variable not found
	return appData;
#endif

	static char configPath[MAX_PATH_LENGTH]; // static buffer to avoid dealloc

	const char *homeDir = getenv("HOME");
	if (homeDir == NULL)
		return NULL; // Error: HOME environment variable not found

#ifdef __linux__ // LINUX	
	int fmtRet = snprintf(configPath, sizeof(configPath), "%s/.config", homeDir);
#elif __APPLE__ // MACOS
	int fmtRet = snprintf(configPath, sizeof(configPath), "%s/Library/Preferences", homeDir);
#endif

	if (fmtRet < 0 || fmtRet > sizeof(configPath))
		return NULL; // Error: Formatting failed or buffer overflow

	return configPath;
}

int main(void) {

#ifdef _WIN32 // WINDOWS
	char divider = '\\';
#else // UNIX
	char divider = '/';
#endif

	char configPath[MAX_PATH_LENGTH];
	const char *configDir = getConfigDirectory();

	int fmtRet = snprintf(configPath, sizeof(configPath), "%s%cwebbox%cdefault.cfg", configDir, divider, divider);
	if (fmtRet < 0 || fmtRet > sizeof(configPath)) {
		printf("  [ERROR] Unable to format 'configPath'\n");
		return 1;
	}

	FILE *file = NULL;

	if ((file = fopen(configPath, "r")) == NULL) {
		printf("  [ERROR] Unable to read '%s'\n", configPath);
		return 1;
	}

	char line[MAX_LINK_LENGTH];

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

// TODO: test the config path if it works on MacOS and Windows
// TODO: automatic setup of the config file if it doesn't exist
// TODO: write a string formatting lib for easier use
// TODO: add section support for setup, links and more