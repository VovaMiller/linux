set number

filetype plugin indent on
" show existing tab with 4 spaces width
set tabstop=4
" when indenting with '>', use 4 spaces width
set shiftwidth=4
" On pressing tab, insert 4 spaces
set expandtab

" :PlugInstall
call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdcommenter'
Plug 'terryma/vim-smooth-scroll'
call plug#end()

" Relative line numbers along with absolute ones
" https://www.vim.org/scripts/script.php?script_id=2351
"RltvNmbr
" I didn't manage to make it autoload.
" It lags really hard. So just active classic hybrid line number mode.
set rnu

nnoremap th  :tabfirst<CR>
nnoremap tk  :tabnext<CR>
nnoremap tj  :tabprev<CR>
nnoremap tl  :tablast<CR>

" accidental Caps Lock
map ZZ  :echo "ZZ was deprecated"<CR>

noremap <silent> <c-u> :call smooth_scroll#up(&scroll, 10, 1)<CR>
noremap <silent> <c-d> :call smooth_scroll#down(&scroll, 10, 1)<CR>
noremap <silent> <c-b> :call smooth_scroll#up(&scroll*2, 10, 4)<CR>
noremap <silent> <c-f> :call smooth_scroll#down(&scroll*2, 10, 4)<CR>

