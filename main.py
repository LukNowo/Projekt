import pygame
from game import Game_Window


#barvy
Black = (102, 128, 150)
white = (255, 255, 255)


#souřadnice
xB = 0 
yB = 0
w = 0
h = 0

#tabulka
user_key = ''
comp_key = ''

def print_option(screen, color, xB, yB):
    font_style = pygame.font.Font("Minecraft.ttf", 35)
    font_style_sub = pygame.font.Font("Minecraft.ttf", 25)
    msg = "Vyber si symbol:"
    mesg = font_style.render(msg, True, color)
    screen.blit(mesg, [xB+70, yB+150])

    msgX = "Zmackni X: Hrac_X"
    msgY = "Zmackni O: Hrac_O"
    mesgX = font_style_sub.render(msgX, True, color)
    mesgY = font_style_sub.render(msgY, True, color)
    screen.blit(mesgX, [xB+90, yB+190])
    screen.blit(mesgY, [xB+90, yB+220])

def user_screen():
    global xB, yB, user_key, comp_key
    running = True
    screenDim = pygame.display.set_mode((400, 400), pygame.RESIZABLE)
    pygame.display.set_caption('Hra piškvorky') 

    while(running): 
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.VIDEORESIZE:
                screenDim = pygame.display.set_mode((event.w, event.h), pygame.RESIZABLE)
                screenDim.fill(Black) 
                w, h = pygame.display.get_surface().get_size() 
                if w!=400:
                     xB = (w-400)/2
                     yB = (h-400)/2  
                else:
                    xB = 0
                    yB = 0
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_x:
                    user_key = 'x'
                    comp_key = 'o'
                elif event.key == pygame.K_o:
                    user_key = 'o'
                    comp_key = 'x'
                else:
                    break
                Game_Window(screenDim, user_key)
                running = False
                
        if(running == True):
            screenDim.fill(Black)
            print_option(screenDim, white, xB, yB) 
            pygame.display.update()

pygame.init()
user_screen()
pygame.quit()
quit()