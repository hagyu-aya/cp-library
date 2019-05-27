def source2snipet(source_file_name, output_file_name):
    with open(source_file_name) as i:
        with open(output_file_name, "w") as o:
            for line in i.readlines():
                o.write('"' + line[:-1] + '",\n')

if __name__ == "__main__":
    i, o = input(), input()
    source2snipet(i, o)
