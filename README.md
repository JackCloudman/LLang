# Lala Lang!
This is a program language OOP using yacc and lex
## Information
### Strings
Show messages in your programs, now  you can put strings as:
```python
text =  "My awesome text"
```
Some operations are:
```python
text = "x :" + x # Convert object to text
message = "hello "+ "world" # concatenate strings
```
### Arrays
Store multiples objects as!
```
arr =  [1,2,3,4,"hello","world",[6,7]]
```
**Operations**
```
[1,2,3]+[4,5,6] #Merge arrays with operator '+'
arr[0] #Access to array data (index start in 0)
arr[-1] # Yes! you can use negative numbers to get data of right to left
arr[0] = 3 # Change array values 
```
**Duplicate arrays**
```
x = y = [1,2,3] #Copy same reference
x = [1,2,3] #To make different arrays merge second array with empty array
y = x+[ ] # x and y are different arrays with same values
```
