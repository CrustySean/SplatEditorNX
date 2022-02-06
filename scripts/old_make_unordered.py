import re
from itertools import tee, islice, chain

def isNum(num):
    return bool(re.search(r'\d', num))

# https://stackoverflow.com/a/1012089
def previous_and_next(some_iterable):
    prevs, items, nexts = tee(some_iterable, 3)
    prevs = chain([None], prevs)
    nexts = chain(islice(nexts, 1, None), [None])
    return zip(prevs, items, nexts)

out = open('outS.txt','w+')
with open(f'Shoes_Database.txt') as f:
    lines = f.readlines()
    temp = [line[:-1] for line in lines]

    out.write(f'/* Automatically generated trough the make_unordered.py script. */')
    out.write(f'\n')

    for previous, item, nxt in previous_and_next(temp):
        if item != '' and isNum(item) and not nxt == '':
            if nxt == '???':
                nxt = -1
            out.write('{"%s", %s},' % (item, nxt))
            out.write('\n')

out.write(f'/* End of the generated code. */')
out.close()
