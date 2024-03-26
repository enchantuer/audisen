# Audisen

### To build
```bash
make usb
```
```bash
make simulation
```
```bash
make autotests
```

### Usb
Work with .txt, .amp, .ams file
```bash
.\build\usb.exe <file_name>
```

### Simulation
Work with .txt, .ams file
```bash
.\build\simulation.exe <file_name>
```

### Autotests
You need to have `bohemian_rhapsody.txt` and `bohemian_rhapsody.ams` file in the build folder, add them to build folder
```bash
cp music/bohemian_rhapsody.txt ./
cp music/bohemian_rhapsody.ams ./
```
```bash
.\build\autotests.exe
```
