import requests
import os
from PIL import Image
from pathlib import Path

# Download the logo image
print('Downloading logo...')
url = 'https://raw.githubusercontent.com/Leanny/leanny.github.io/master/splathex/splathex2logo.png'
r = requests.get(url, allow_redirects=True)

# Open the logo image
print('Opening logo...')
open('splathex2logo.png', 'wb').write(r.content)

# Rename logo
print('Renaming logo...')
os.rename('splathex2logo.png', 'tmp_app_icon.png')

# Convert our png to jpg
print('Converting logo to jpg...')
png = Image.open('tmp_app_icon.png').convert('RGB')
png.load()
png.save('tmp_h_icon.jpg')

# Open logo
print('Opening logo...')
h_icon = Image.open('tmp_h_icon.jpg')
app_icon = Image.open('tmp_app_icon.png')

# Resize it
print('Resizing logo...')
resizedjpg = h_icon.resize((295, 256))
resizedpng = app_icon.resize((295, 256))
resizedjpg.save('h_icon.jpg')
resizedpng.save('app_icon.png')

# Move the logo from the current directory to the resources/img directory
print('Moving logo to resources/img...')

Path('tmp_h_icon.jpg').rename('resources/img/h_icon.png')
Path('tmp_app_icon.png').rename('resources/img/app_icon.png')

# Remove temp files
print('Removing temp files...')
os.remove('h_icon.jpg')
os.remove('app_icon.png')
