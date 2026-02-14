# Use 'do' blocks to pass a custom aggregation function to 'combine(groupby(...))'

# tax 10% only from the ones with 100$+ in sales.

using DataFrames

df = DataFrame(
    City = ["Dhaka", "Dhaka", "Delhi", "Delhi", "NYC", "NYC"],
    Sales = [150.0, 50.0, 200.0, 80.0, 300.0, 40.0]
)

# Step 1: Group the data
grouped_df = groupby(df, :City)

# Step 2: Use 'combine' with a 'do' block
result = combine(grouped_df) do sub_df
    # 'sub_df' represents the small piece of the dataframe for each city
    high_value_sales = sub_df.Sales[sub_df.Sales .> 100]
    
    total = sum(high_value_sales)
    taxed_total = total * 0.9
    
    # Return a Named Tuple to define the new column names
    return (Adjusted_Revenue = taxed_total, Count = length(high_value_sales))
end

println(result)

# DataFrames.jl is Julia's version of pandas.
# DataFrame() function creates a table-- already values passed in which creates a   table there.
# City would be a variable name. :City --> column named city. A word starting with  a colon is a symbol.
# sub_df is a temporary variable name. Represents the mini-table for one specific   city. So it has a Sales column as its a subset.
# combine(...) do sub_df is a function same as-- function F(sub_df) ... end and th  en passing it to combine.
# [] are for targetted columns but matching the rule.
# return named tuples.Rewrites the result variable content. And also city will be there cause it is the group.
# end is for the do block. Which is secretly a function.
# The do block is a loop. Julia says: "Okay, give the first group to the do block   and call it sub_df
# Loop 1 (Dhaka): The do block runs for Dhaka. It returns (Adjusted_Revenue = 135.  0, Count = 1). combine catches this and puts it in a "waiting room."
# Loop 2 (Delhi): The do block runs for Delhi. It returns (Adjusted_Revenue = 180.  0  , Count = 1). combine catches this too.
# Loop 3 (NYC): The do block runs for NYC. It returns (Adjusted_Revenue = 270.0, C  o  unt = 1).
# combine takes those three separate results and "stacks" them on top of each othe  r. It also automatically adds the grouping column (City) back so you know which   row belongs to which city.
# DataFrame(...), you are calling a Constructor—you are telling Julia, "Hey, build me a new object using the blueprint for a DataFrame."
