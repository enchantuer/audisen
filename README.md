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
```bash
make autotests
make simulation
make usb
```

### Usb
Work with .txt, .amp, .ams file
```bash
.\test_usb.exe <file_name>
```

### Simulation
Work with .txt, .ams file
```bash
.\test_sim.exe <file_name>
```
```bash
py play.py
```
```bash
.\test_sim.exe <file_name>
py play.py
```

### Autotests
You need to have `bohemian_rhapsody.txt` and `bohemian_rhapsody.ams` file in the root folder of the project
```bash
.\test_autotests.exe
```
