from PIL import ImageColor,Image,ImageDraw
import os
import csv
import imageio


def make_pictures(csv_file, png_path = "imgs/", seed_png = "seed.png"):
    print(png_path)
    if not os.path.exists(png_path):
        os.makedirs(png_path)
    with open(csv_file) as f:
        f_csv = csv.reader(f)
        it = 0
        for it, row in enumerate(f_csv):
            if it%2 == 0:
                portion = row
                x_total_num = len(portion)
                continue
            else:
                colors = row
            with Image.open(seed_png) as im:
                draw = ImageDraw.Draw(im)
                for i in range(x_total_num):
                    draw.rectangle(xy = [i*(im.size[0]/x_total_num) + 4, 
                    im.size[1]-float(portion[i])*(2*im.size[1]/3)/100, 
                    (i+1)*im.size[0]/x_total_num, 
                    im.size[1]], 
                    fill=ImageColor.getrgb(colors[i]))
                im.save(png_path+str(it)+".png")
        return it

def create_gif(image_list, gif_name, duration=0.5): 
    frames = [] 
    for image_name in image_list:
        frames.append(imageio.imread(image_name)) 
        imageio.mimsave(gif_name, frames, 'GIF', duration=duration)
    return


if __name__ == '__main__': 
    make_pictures("dar.csv")
    create_gif(['./imgs/'+str(i)+'.png' for i in range(1,6,2)], "demo.gif")
