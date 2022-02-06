import json
import os

user = input('Enter file name: ')

prfx = input('Enter prefix: ')

# Check file extension
if not ('.json' in user):
    print('Invalid json file')
    exit()

# Check prefix
if not ('Wst' or 'Wsb' or 'Wsp' or 'Clt' or 'Shs' or 'Hed' in prfx):
    print('Invalid prefix')
    exit()

with open(user, 'r') as f:
    weapons = json.load(f)

f = open('out_' + user.replace('.json', '.txt'), 'w')
f.write('/* Automatically generated trough the make.py script. */')
f.write('\n')
f.write('std::unordered_map<std::string, int> %s {' % user.replace('.json', ''))
f.write('\n')

for i in weapons:
    f.write('   {"%s_%s", %s},' % (prfx, i['Name'], i['Id']))
    f.write('\n')

f.write('};')
f.write('\n')
f.write('/* End of the generated code. */')
f.close()

choice = input('Do you want to generate download code? ')

if not (choice == 'yes' or choice == 'y' or choice == 'Y' or choice == 'Yes'):
    exit()

# Need a way to automatically delete last comma before ]
q = open('d_' + user.replace('.txt', ''), 'w')
q.write('[\n')

for i in weapons:
    q.write('  {')
    q.write('\n    "url":"https://leanny.github.io/splat2/subspe/%s_%s.png",\n    "sdpath":"sdmc:/SplatEditor/Cache/%s_%s.png"' % (prfx, i['Name'], prfx, i['Name']))
    q.write('\n  },\n')

q.write(']\n')

q.close()
