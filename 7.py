#Write a script that uses 'argparse' to accept command-line arguments for input file and output directory.


#!/usr/bin/env python3
import argparse
import os

def main():
    #  Create the argument parser
    parser = argparse.ArgumentParser(
        description="Process an input file and write results to an output directory"
    )

    # Add arguments
    parser.add_argument(
        "-i", "--input",
        required=True,
        help="Path to the input file"
    )

    parser.add_argument(
        "-o", "--output-dir",
        required=True,
        help="Path to the output directory"
    )

    # Parse the arguments
    args = parser.parse_args()

    input_file = args.input
    output_dir = args.output_dir

    # Optional: validate paths
    if not os.path.isfile(input_file):
        print(f"Error: Input file '{input_file}' does not exist.")
        exit(1)

    if not os.path.isdir(output_dir):
        print(f"Error: Output directory '{output_dir}' does not exist.")
        exit(1)

    print(f"Input file: {input_file}")
    print(f"Output directory: {output_dir}")

    # Example: do something with the file
    with open(input_file, "r") as f:
        content = f.read()

    # Just for demonstration: write content to a new file in output dir
    output_file = os.path.join(output_dir, "output.txt")
    with open(output_file, "w") as f:
        f.write(content)

    print(f"Content written to {output_file}")

if __name__ == "__main__":
    main()


#This is a dummy data pipelining script. Core pipeline concepts--
#1.Stage seperation, 2.Stateless processing, 3.Deterministic outputs, 4.File-based interfaces, 5.CLI contracts, 6.Input/Output boundaries, 7.Transformation isolatio n, 8.Reusability, 9.Composability.

