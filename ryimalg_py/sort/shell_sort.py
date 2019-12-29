import csv


class ShellSort:
    def sort(self, comparable_list):
        length = len(comparable_list)
        h = 1
        # 1, 4, 13, 40, 121,364,1093, ...
        while h < (length // 3):
            h = 3 * h + 1
        while h >= 1:
            for i in range(h, length):
                for j in range(i, 0, -h):
                    if j>=h and comparable_list[j] < comparable_list[j-h]:
                        comparable_list[j], comparable_list[j-h] = comparable_list[j-h], comparable_list[j]
            h = h//3

    def sort_gif(self, comparable_list, csv_path="sort_info.csv"):
        length = len(comparable_list)
        h = 1
        with open(csv_path,'w+', newline='') as file:
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(50,50,50)" for _ in range(length)]
            content.writerow(comparable_list)
            content.writerow(colors)
            # 1, 4, 13, 40, 121,364,1093, ...
            while h < (length // 3):
                h = 3 * h + 1
            # start to sort
            while h >= 1:
                for i in range(h, length):
                    for j in range(i, 0, -h):
                        # content.writerow(comparable_list)
                        # colors = ["rgb(50,50,50)" for _ in range(length)]
                        # colors[i] = "rgb(250,50,50)"
                        # content.writerow(colors)
                        if j >= h and comparable_list[j] < comparable_list[j-h]:
                            comparable_list[j], comparable_list[j-h] = comparable_list[j-h], comparable_list[j]
                        content.writerow(comparable_list)
                        colors = ["rgb(50,50,50)" for _ in range(length)]
                        colors[j] = "rgb(0,0,0)"
                        colors[j-h] = "rgb(0,0,0)"
                        content.writerow(colors)
                h = h//3
