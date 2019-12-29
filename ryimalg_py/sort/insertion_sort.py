import csv


class InsertionSort:
    def sort(self, comparable_list):
        length = len(comparable_list)
        for i in range(1, length):
            for j  in range(i, 0, -1):
                if comparable_list[j] < comparable_list[j-1]:
                    comparable_list[j], comparable_list[j-1] = comparable_list[j-1], comparable_list[j]
                else:
                    break

    def sort_gif(self, comparable_list, csv_path="sort_info.csv"):
        length = len(comparable_list)
        with open(csv_path,'w+', newline='') as file:
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(50,50,50)" for _ in range(length)]
            content.writerow(comparable_list)
            content.writerow(colors)
            for i in range(1, length):
                content.writerow(comparable_list)
                colors = ["rgb(50,50,50)" for _ in range(length)]
                colors[i] = "rgb(250,50,50)"
                content.writerow(colors)
                for j  in range(i, 0, -1):
                    if comparable_list[j] < comparable_list[j-1]:
                        comparable_list[j], comparable_list[j-1] = comparable_list[j-1], comparable_list[j]
                        content.writerow(comparable_list)
                        colors[j]   = "rgb(0,0,0)"
                        colors[j-1] = "rgb(0,0,0)"
                        content.writerow(colors)
                    else:
                        break
            content.writerow(comparable_list)
            colors[i] = "rgb(250,50,50)"
            content.writerow(colors)
