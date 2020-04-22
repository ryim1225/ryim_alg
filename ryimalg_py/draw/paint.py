from PIL import ImageColor,Image,ImageDraw
import os
import csv
import imageio


def make_pictures_of_barchart(csv_file, png_path = "imgs/", seed_png = "seed.png"):
    if not os.path.exists(png_path):
        os.makedirs(png_path)
    with open(csv_file) as f:
        f_csv = csv.reader(f)
        it = 0
        for it, row in enumerate(f_csv):
            if it%2 == 0:
                portion = [float(i) for i in row]
                #print(portion)
                max_value = max(portion)
                #print("max value: {}".format(max_value))
                x_total_num = len(portion)
                continue
            else:
                colors = row
            with Image.open(seed_png) as im:
                draw = ImageDraw.Draw(im)
                for i in range(x_total_num):
                    #print("portion: {}".format(portion[i]/max_value))
                    draw.rectangle(xy = [
                        i*(im.size[0]/x_total_num) + 4, 
                        im.size[1] * (1 - portion[i]/max_value*(2/3)),
                        (i+1)*im.size[0]/x_total_num, 
                        im.size[1]
                        ], 
                    fill=ImageColor.getrgb(colors[i]))
                im.save(png_path+str(it)+".png")
        return it

class paint_node:
    def __init__(self):
        self.name = None
        self.color_edges = None
        self.subnodes = None
        self.color = None


def make_picture_of_tree():
    pass


def create_gif(image_list, gif_name, duration=0.5): 
    frames = [] 
    for image_name in image_list:
        frames.append(imageio.imread(image_name)) 
        imageio.mimsave(gif_name, frames, 'GIF', duration=duration)
    return


if __name__ == '__main__': 
    make_pictures_of_barchart("dar.csv")
    create_gif(['./imgs/'+str(i)+'.png' for i in range(1,6,2)], "demo.gif")
