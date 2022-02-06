import os
arr = os.listdir('gears')

weapons = open('gears.cpp', 'w') 
weapons.write('/* Automatically generated trough the gears.py script. */') 
weapons.write("\n")

for file in arr:
    if file.endswith('.png'):
        weapons.write('Cache::DownloadImage("https://github.com/Leanny/leanny.github.io/tree/master/splat2/gear/{}", "sdmc:/SplatEditor/Cache/gears/{}");'.format(file, file))
        weapons.write("\n")
weapons.write('/* End of the generated code. */')
weapons.write('\n')
weapons.close() 
