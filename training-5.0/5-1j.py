# https://contest.yandex.ru/contest/59539/problems/J/

class MyImage:
    def __init__(self):
        layout = ""  # 1 - embedded, 2 - surrounded, 3 - floating
        self.width = self.height = self.dx = self.dy = self.x = self.y = 0

    def __init__(self, str_image: str):
        def readParam(name_param: str) -> int:
            pos1 = str_image.find(name_param + "=")
            if pos1 == -1: return 0
            pos1 += len(name_param) + 1
            pos2 = min(str_image.find(" ", pos1), str_image.find(")", pos1))
            res = str_image[pos1:pos2]
            if name_param == "layout":
                res = layouts[res]
            return int(res)

        layouts = {"embedded": 1, "surrounded": 2, "floating": 3}
        str_image = str_image.replace(" = ", "=")
        self.layout = readParam("layout")
        self.height = readParam("height")
        self.width = readParam("width")
        self.dx = readParam("dx")
        self.dy = readParam("dy")
        self.x = self.y = 0

    def updateCoordinates(self, new_x: int, new_y: int):
        self.x = new_x
        self.y = new_y


class MyDocument:
    images: MyImage = []
    CurrImage: MyImage
    areas = []

    def __init__(self, width, line_height, char_width):
        self.width = width
        self.line_height = line_height
        self.char_width = char_width
        self.x = 0
        self.y = 0
        self.curr_line_height = line_height
        self.is_need_space = False
        self.areas.append([self.width, self.width + 1])
        self.idx_image = self.idx_last_floating = -1
        self.has_surrounded = False
        self.CurrImage = None

    def fillAreas(self):
        y0 = self.y
        y1 = y0 + self.curr_line_height
        self.areas.clear()
        for image in self.images:
            if image.layout == 2 and y1 > image.y and y0 < image.y + image.height:
                self.areas.append([image.x, image.x + image.width])
        if len(self.areas) > 1: self.areas.sort()
        self.areas.append([self.width, self.width + 1])

    def findPos(self, new_width: int):
        if self.has_surrounded:
            self.fillAreas()
        while True:
            for area in self.areas:
                if area[0] < self.x: continue
                if self.is_need_space:
                    if area[0] >= self.x + new_width + self.char_width:
                        self.x += self.char_width
                        return
                else:
                    if area[0] >= self.x + new_width: return
                self.is_need_space = False
                self.x = area[1]
            self.insertLine()
            self.fillAreas()

    def insertLine(self):
        self.x = 0
        self.y += self.curr_line_height
        self.curr_line_height = self.line_height
        self.is_need_space = False
        self.idx_last_floating = -1

    def insertWord(self, word: str):
        new_width = self.char_width * len(word)
        self.findPos(new_width)
        self.x += new_width
        self.is_need_space = True
        self.idx_last_floating = -1

    def insertImage(self, str_image: str):
        new_image = MyImage(str_image)
        match new_image.layout:
            case 1: # embedded
                new_width = new_image.width
                self.findPos(new_width)
                self.is_need_space = True
                self.curr_line_height = max(self.curr_line_height, new_image.height)
            case 2: # surrounded
                new_width = new_image.width
                self.is_need_space = False
                self.findPos(new_width)
                self.has_surrounded = True
            case 3: # floating
                if self.idx_last_floating > -1:
                    prev_image = self.images[self.idx_last_floating]
                    tmp_x = prev_image.x + prev_image.width
                    tmp_y = prev_image.y
                else:
                    tmp_x = self.x
                    tmp_y = self.y
                tmp_x = max(0, tmp_x + new_image.dx)
                if tmp_x + new_image.width > self.width:
                    tmp_x = self.width - new_image.width
                tmp_y += new_image.dy
                new_image.updateCoordinates(tmp_x, tmp_y)
        if new_image.layout < 3:
            new_image.updateCoordinates(self.x, self.y)
            self.x += new_width
            self.idx_last_floating = -1
        else:
            self.idx_last_floating = self.idx_image + 1
        self.idx_image += 1;
        self.images.append(new_image)
        self.CurrImage = self.images[self.idx_image]

    def parse(self, buffer):
        idx = 0
        while idx < len(buffer):
            if buffer[idx] == " ":
                idx += 1
                continue
            if buffer[idx] == '\n':
                self.insertLine()
                idx += 1
            elif buffer[idx:idx + 6] == "(image":
                next_pos = min(buffer.find(")", idx), len(buffer))
                image = buffer[idx: next_pos + 1]
                self.insertImage(image)
                idx = next_pos + 2
            else:
                next_pos = min(buffer.find(" ", idx), len(buffer))
                word = buffer[idx: next_pos]
                self.insertWord(word)
                idx = next_pos + 1


with open("input.txt", "r") as fin:
    w, h, c = map(int, fin.readline().split())
    buffer = ""
    for line in fin:
        if line != "\n": line = line.replace("\n", " ")
        buffer += line
doc = MyDocument(w, h, c)
doc.parse(buffer)

for image in doc.images:
    print(image.x, image.y)
