import json

config_file = './config.d/config.json'
header_file = './include/config.h'

with open(config_file) as f:
    config = json.load(f)

with open(header_file, 'w') as f:
    f.write("#ifndef CONFIG_H\n#define CONFIG_H\n")
    for key, value in config.items():
        f.write(f'#define {key.upper()} "{value}"\n')
    f.write(f'#endif\n\n')
