#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEFAULT_INTERVAL 180
#define DEFAULT_VOLUME 100

#define LVL_HIGH 90
#define LVL_LOW_1 40
#define LVL_LOW_2 30
#define LVL_LOW_3 20
#define LVL_LOW_4 10
#define LVL_LOW_5 5

#define CMD_PLAY_PREFIX "ffplay -loglevel panic -nodisp -autoexit"
#define CMD_OPT_VOLUME "-volume"
#define CMD_OPT_INPUT "-i"
#define SND_PREFIX "~/Sounds/"
#define SND_HIGH SND_PREFIX"snd_charge_high.wav"
#define SND_LOW_1 SND_PREFIX"snd_charge_low_1.wav"
#define SND_LOW_2 SND_PREFIX"snd_charge_low_2.wav"
#define SND_LOW_3 SND_PREFIX"snd_charge_low_3.wav"
#define SND_LOW_4 SND_PREFIX"snd_charge_low_4.wav"
#define SND_LOW_5 SND_PREFIX"snd_charge_low_5.wav"

#define PRC_FMT "%hu"
typedef unsigned short percentage_t;

#define STATE_DISCHARGING -1
#define STATE_UNKNOWN 0
#define STATE_CHARGING 1

percentage_t get_percentage() {
    percentage_t percentage;
    FILE *fp = popen("upower -i `upower -e | grep 'BAT'` | sed -n '/percentage/ s/[^0-9]//g p'", "r");
    if (fp == NULL) return 0;
    fscanf(fp, PRC_FMT, &percentage);
    pclose(fp);
    return percentage;
}

// TODO: why did you remove -i autofinder (like it is now in get_percentage)
int get_state() {
    char buffer[256];
    FILE *fp = popen("upower -i /org/freedesktop/UPower/devices/battery_BAT0 | sed -n '/state:/ s/state:// p' | sed -n 's/\\s//g p'", "r");
    if (fp == NULL) return STATE_UNKNOWN;
    fscanf(fp, "%s", buffer);
    pclose(fp);
    if (strcmp(buffer, "charging") == 0) return STATE_CHARGING;
    if (strcmp(buffer, "discharging") == 0) return STATE_DISCHARGING;
    return STATE_UNKNOWN;
}

void check_charge(unsigned int volume) {
    char cmd[1024];
    char vlm[4];
    size_t cmd_len = 0;
    size_t len;

    sprintf(vlm, "%d", volume);
    memcpy(cmd + cmd_len, CMD_PLAY_PREFIX, strlen(CMD_PLAY_PREFIX));
    cmd_len += strlen(CMD_PLAY_PREFIX);
    memcpy(cmd + cmd_len, " "CMD_OPT_VOLUME, strlen(CMD_OPT_VOLUME) + 1);
    cmd_len += strlen(CMD_OPT_VOLUME) + 1;
    memcpy(cmd + cmd_len, " ", 1);
    cmd_len += 1;
    memcpy(cmd + cmd_len, vlm, strlen(vlm));
    cmd_len += strlen(vlm);
    memcpy(cmd + cmd_len, " "CMD_OPT_INPUT, strlen(CMD_OPT_INPUT) + 1);
    cmd_len += strlen(CMD_OPT_INPUT) + 1;

    percentage_t percentage = get_percentage();
    int state = get_state();

    if (state == STATE_CHARGING) {
        if (percentage > LVL_HIGH) {
            len = strlen(SND_HIGH) + 1; 
            memcpy(cmd + cmd_len, " "SND_HIGH, len);
            cmd_len += len;
        }
    } else if (state == STATE_DISCHARGING) {
        if (percentage < LVL_LOW_5) {
            len = strlen(SND_LOW_5) + 1;
            memcpy(cmd + cmd_len, " "SND_LOW_5, len);
            cmd_len += len;
        } else if (percentage < LVL_LOW_4) {
            len = strlen(SND_LOW_4) + 1;
            memcpy(cmd + cmd_len, " "SND_LOW_4, len);
            cmd_len += len;
        } else if (percentage < LVL_LOW_3) {
            len = strlen(SND_LOW_3) + 1;
            memcpy(cmd + cmd_len, " "SND_LOW_3, len);
            cmd_len += len;
        } else if (percentage < LVL_LOW_2) {
            len = strlen(SND_LOW_2) + 1;
            memcpy(cmd + cmd_len, " "SND_LOW_2, len);
            cmd_len += len;
        } else if (percentage < LVL_LOW_1) {
            len = strlen(SND_LOW_1) + 1;
            memcpy(cmd + cmd_len, " "SND_LOW_1, len);
            cmd_len += len;
        }
    } else {
        return;
    }

    cmd[cmd_len] = '\0';
    system(cmd);
}

int main(int argc, char *argv[]) {
    int opt, t, v;
    unsigned int interval = DEFAULT_INTERVAL;
    unsigned int volume = DEFAULT_VOLUME;

    // Reading arguments.
    while ((opt = getopt(argc, argv, ":v:t:")) != -1) {  
        switch (opt) {  
            case 'v':
                v = atoi(optarg);
                if ((v > 0) && (v <= 100)) {
                    volume = v;
                } else {
                    printf("wrong value for option '%c'\n", opt);
                }
                break;  
            case 't':
                t = atoi(optarg);
                if (t > 0) {
                    interval = t;
                } else {
                    printf("wrong value for option '%c'\n", opt);
                }
                break;  
            case ':':  
                printf("option '%c' needs a value\n", optopt);  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;  
        }
    }
    fflush(stdout);

    // Main loop.
    while (1) {
        check_charge(volume);
        sleep(interval);
    }
    return 0;
}

