import os


def build():
    cpp_files = [f for f in os.listdir('.') if f.endswith('.cpp')]
    with open('output.md', 'w') as md_file:
        for cpp_file in cpp_files:
            md_file.write(f"{cpp_file}\n\n")
            md_file.write("```cpp\n")
            with open(cpp_file, 'r') as file:
                md_file.write(file.read())
            md_file.write("\n```\n\n")


if __name__ == "__main__":
    build()
