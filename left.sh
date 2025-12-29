#!/bin/bash

while IFS= read -r line; do
    [[ -n "$line" ]] || continue
    win_id=${line%% *}
    wmctrl -i -r "$win_id" -e 0,0,0,1285,720
done < <(wmctrl -l | grep -i 'qq')
