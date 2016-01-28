import pylab as plt

plt.figure(1, figsize=(5, 5))

# ax2 = plt.axes([0.5, 0.5, 0.8, 0.8])


class MakeMultipleCharts(object):

    def __init__(self, number_of_rows, number_of_columns, space_to_preserve_x, space_to_preserve_y, names_to_fractions):
        self.number_of_rows = number_of_rows
        self.number_of_columns = number_of_columns
        self.space_to_preserve_x = space_to_preserve_x
        self.space_to_preserve_y = space_to_preserve_y
        self.names_to_fractions = names_to_fractions
        self.rectangles = []
        self.generateSpace()


    def generateSpace(self):
        x_space_left = 1.0 - self.space_to_preserve_x
        y_space_left = 1.0 - self.space_to_preserve_y
        x_per_axe = x_space_left / self.number_of_columns
        y_per_axe = y_space_left / self.number_of_rows
        x_white_per_axe = self.space_to_preserve_x / (self.number_of_columns + 1)
        y_white_per_axe = self.space_to_preserve_y / (self.number_of_rows + 1)
        rectangles = list()

        current_y = 0

        for i in range(self.number_of_rows):

            from_down = current_y + y_white_per_axe
            height = y_per_axe
            current_x = 0
            for j in range(self.number_of_columns):
                from_left = current_x + x_white_per_axe
                width = x_per_axe
                rectangles.append([from_left, from_down, width, height])
                current_x += from_left + width

            current_y += from_down + height

        self.rectangles = rectangles

    def render(self):
        self.generateSpace()
        self.axes = list()
        for i, rectangle in enumerate(self.rectangles):
            ax = plt.axes(rectangle)

            keys = list(self.names_to_fractions[i].keys())
            keys.sort()

            labels = keys
            fractions = list()

            for key in keys:
                fractions.append(self.names_to_fractions[i][key] * 100)

            explode = tuple(0.05 for i in range(len(fractions)))
            plt.pie(fractions, explode=explode, labels=labels, autopct='%1.1f%%', shadow=True, startangle=90)
            self.axes.append(ax)

        plt.show()






# plt.show()
# rectangles = makeMultipleCharts(2, 2, 0.1, 0.1)

