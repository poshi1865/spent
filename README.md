This is a program I wrote to track my expenses. You can enter the amount spent and the item you spent it on.
The list as well as the total for different months can be fetched by specifying it in the arguments.


usage:
```
spent amount spent_on
        This will store the amount with the thing you spent it on

spent --total month_number(1-12)
        This will give you the total amount you have spent in the specified month

spent --list month_number(1-12)
        This will give you the amount and the list of items for the specified month
```

```
$ ./spent 157 food
Amount: 157
Spent on: food
```

```
$ ./spent --list 2
199 cab
272 takeaway
15 coffee
```

```
$ ./spent --total 2
Total Spent: 886
```

Installation:
clone this project, go into the project folder and run:
```
chmod u+x install.sh
./install.sh
```

