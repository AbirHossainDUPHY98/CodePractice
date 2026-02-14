#Chain operations using 'pandas' method chaining to clean and summarize a dataset in one expression.

# Operations to chain-- 
#.drop(columns=...) → remove columns

#.rename(columns=...) → rename columns
#
#.fillna(...) → fill missing values
#
#.astype(...) → convert data type
#
#.query(...) → filter rows
#
#.assign(...) → add new column
#
#.groupby(...).agg(...) → aggregation
#
#.sort_values(...) → sort

import pandas as pd

result = (
    pd.read_csv("https://raw.githubusercontent.com/mwaskom/seaborn-data/master/taxis.csv")
      # Standardize column names
      .rename(columns=lambda c: c.strip().lower())
      # Drop rows with essential missing
      .dropna(subset=["fare", "distance", "pickup"])
      # Parse date/time-- converts string-> Datetime object
      .assign(pickup_datetime=lambda df: pd.to_datetime(df["pickup"]))
      # Derive a new feature-- creates a pickup_hour column
      .assign(pickup_hour=lambda df: df["pickup_datetime"].dt.hour)
      # Filter out unrealistic values
      .query("distance > 0 and fare > 0")
      # Group & summarize--> groups rows by hour, keep pickup_hour as a column, not an index - groups are not visible, but index mapped
      .groupby("pickup_hour", as_index=False)
      #new_column_name = (source_column, operation) for each pickup_hour
      .agg(
          avg_fare=("fare", "mean"),
          avg_dist=("distance", "mean"),
          count_trips=("fare", "count")
      )
      # Sort by highest average fare
      .sort_values("avg_fare", ascending=False)
      .reset_index(drop=True)
)

print(result)

