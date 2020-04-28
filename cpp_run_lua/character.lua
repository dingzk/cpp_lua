--
-- Created by IntelliJ IDEA.
-- User: zhenkai
-- Date: 2020/4/28
-- Time: 14:23
-- To change this template use File | Settings | File Templates.
--

player = Character.new("Hero", 100)
player:setHealth(80)
hp = player:getHealth()
name = player:getName()
print("Character name: "..name..". HP = "..hp)

--player:free()