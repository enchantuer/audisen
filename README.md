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
Work with .txt, .ams file, add -play-python if you have the python file named play.py and you have python installed on your computer, (the program run the py command you can change it in python.exe if you want)
```bash
.\build\simulation.exe <file_name> (-play-python)
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
