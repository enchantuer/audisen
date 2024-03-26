# Audisen

### To build
```bash
make usb
make simulation
make autotests
```

### Usb
Work with .txt, .amp, .ams file
```bash
.\build\usb <file_name>
```

### Simulation
Work with .txt, .ams file
```bash
.\build\simulation <file_name>
```

### Autotests
You need to have `bohemian_rhapsody.txt` and `bohemian_rhapsody.ams` file in the build folder, add them to build folder
```bash
cp music/bohemian_rhapsody.txt ./ && cp music/bohemian_rhapsody.ams ./
.\build\autotests
```