import csv
import sys
reload(sys)
sys.setdefaultencoding('utf8')


def read_test():
    with open("data.csv", mode="r") as f:
        reader = csv.reader(f)
        header = next(reader)
        for row in reader:
            print("{}{}:{}={}".format(header[0], row[0], header[1], row[1]))


def write_test():
    header_list = ["ID", "CellValue"]
    data_list = [[1, "1_1"], [2, "2_2"], [3, "3_3"]]
    with open("wdata.csv", mode="w") as f:
        writer = csv.writer(f)
        writer.writerow(header_list)
        writer.writerows(data_list)


read_test()
write_test()
