import csv


class SelectionSort:
    def sort(self, comparable_list):
        length = len(comparable_list)
        for i, _ in enumerate(comparable_list):
            min = i
            for j  in range(i+1,length):
                if comparable_list[j] < comparable_list[min]:
                    min = j
            comparable_list[i], comparable_list[min] = comparable_list[min], comparable_list[i]

    def sort_gif(self, comparable_list, csv_path="sort_info.csv"):
        length = len(comparable_list)
        with open(csv_path,'w+', newline='') as file:
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(0,0,0)" for _ in range(length)]
            content.writerow(comparable_list)
            content.writerow(colors)
            for i, _ in enumerate(comparable_list):
                min = i
                for j  in range(i+1,length):
                    if comparable_list[j] < comparable_list[min]:
                        min = j
                content.writerow(comparable_list)
                colors[min] = "rgb(250,50,50)"
                content.writerow(colors)
                comparable_list[i], comparable_list[min] = comparable_list[min], comparable_list[i]
                content.writerow(comparable_list)
                colors[i] = "rgb(50,50,50)"
                if i != min:
                    colors[min] = "rgb(0,0,0)"
                content.writerow(colors)
