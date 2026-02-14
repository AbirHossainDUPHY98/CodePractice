#Use list comprehensions, generator expressions, and 'map/filter' to solve the same filtering problem- compare readability and memory usage... 

# Filter:Keep only transactions greater than $500, Apply 7% tax to those transactions and output in a format ready for a report... Transactions=> [120.50, 890.00, 45.00, 1200.75, 550.00, 20.00, 1500.00 ]

#Transactions = [120.50, 890.00, 45.00, 1200.75, 550.00, 20.00, 1500.00 ]
#list_comprehension = [round(t*1.07, 2) for t in Transactions if t>500.00 ]
#generator_expression = (round(t*1.07, 2) for t in Transactions if t> 500.00 )
#map_filter = map(lambda t:round(t* 1.07, 2),filter(lambda t:t>500.00, Transactions))
#checker = (t for t in Transactions if t>500.00 )
#taxed = (round(t*1.07,2) for t in checker)
#print(list_comprehension) #prints out the data
#print(generator_expression) #prints out the memory addresses
#print(map_filter) #prints out the memory addresses
#print(list(generator_expression))
#print(list(map_filter)) 
#print(list(taxed))

import sys
big_data = range(100000)
list_big = [y*1.07 for y in big_data if y%4==0 ]
generator_big = (y*1.07 for y in big_data if y%4==0 )
map_big = map(lambda x:x*1.07 , filter(lambda x:x%4==0, big_data))
print(f" {sys.getsizeof(list_big)} bytes")
print(f" {sys.getsizeof(generator_big)} bytes")
print(f" {sys.getsizeof(map_big)} bytes")

#Readability: List Comprehensions/Generator Expressions are left to right
            # Map/Filter are inside out
