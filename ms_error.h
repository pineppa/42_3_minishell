/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlgarcia <jlgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:34:26 by josegar2          #+#    #+#             */
/*   Updated: 2024/05/13 22:58:04 by jlgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# define NOTHOME "HOME not set"
# define TOOMANY "too many arguments"
# define OPTARG "%s: option requires an argument"
# define INVOPT "%s: invalid option"
# define INVOPTC "%c%c: invalid option"
# define ISDIR "%s: is a directory"
# define OPENERR "%s: cannot open: %s"
# define EXEERR "%s: cannot execute binary file"
# define INVIDENT "`%s': not a valid identifier"
# define CREAERR "%s: cannot create: %s"
# define NOCLOSE "no closing `%c' in %s"
# define READER_R "%s: cannot read: %s"
# define NUMREQ "%s: numeric argument required"
# define NOTFND "%s: not found"
# define INVNAME "%s: invalid option name"
# define INVNUM "%s: invalid number"
# define WRERROR "write error: %s"
# define DIRERROR "%s: error retrieving current directory: %s: %s"
# define ILLOPT "%s: illegal option -- %c"
# define NOTUNSET "%s: cannot unset"
# define RDONLYUNSET "%s: cannot unset: readonly %s"
# define KEYWORD "%s is a shell keyword"
# define SYNERRS "syntax error: `((%s))'"
# define SYNEOF "syntax error: unexpected end of file"
# define AMBREDIR "%s: ambiguous redirect"
# define NOTOVERWR "%s: cannot overwrite existing file"
# define NOTREDIROUT "%s: restricted: cannot redirect output"
# define NOTHERETEMP "cannot create temp file for here document: %s"
# define SYNERRNUNEXP "syntax error near unexpected token `%s'"
# define SYNERRNEAR "syntax error near `%s'"
# define UNEXPEOF "unexpected EOF while looking for matching `%c'"
# define SLASHINCMD "%s: restricted: cannot specify `/' in command names"
# define CMDNOTFOUND "%s: command not found"
# define SYNERR "syntax error"
# define MAXHERED "maximum here-document count exceeded"
# define SYNERR_NEAR_TOKEN "syntax error near unexpected token `"

#endif
