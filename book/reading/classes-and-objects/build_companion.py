"""Build the reading companion from its editable Markdown and measured outputs.

Run the PDF skill's artifact-operation marker once before an authoring session.
Run code/verify.ps1 first to refresh the verification JSON.
The candidate is rendered for review under tmp/pdfs/cpp-companion. This builder
does not replace the delivered PDF; promote the candidate after visual review.
"""
from pathlib import Path
from html import escape
from urllib.parse import unquote
import hashlib
import json
import re
import sys

from PIL import Image as PILImage
from pypdf import PdfReader
from reportlab.lib import colors
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, PageBreak, Image, Table,
    TableStyle, Preformatted, KeepTogether,
)
from reportlab.graphics.shapes import Drawing, Rect, Line, Polygon, String
from reportlab.graphics import renderSVG
import pypdfium2 as pdfium

sys.stdout.reconfigure(encoding='utf-8')
HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
WORK = ROOT / 'tmp/pdfs/cpp-companion'
WORK.mkdir(parents=True, exist_ok=True)
WIDTH = A4[0] - 113.4
FONT_FOLDER = Path('C:/Windows/Fonts')
for name, filename in [('Body', 'arial.ttf'), ('BodyBold', 'arialbd.ttf'),
                       ('Mono', 'consola.ttf')]:
    pdfmetrics.registerFont(TTFont(name, str(FONT_FOLDER / filename)))
pdfmetrics.registerFontFamily('Body', normal='Body', bold='BodyBold')
NAVY = colors.HexColor('#002060')
BLUE = colors.HexColor('#0563C1')
INK = colors.HexColor('#20252b')
styles = {
    'title': ParagraphStyle('Title', fontName='BodyBold', fontSize=23,
        leading=28, textColor=NAVY, spaceAfter=7),
    'heading': ParagraphStyle('Heading', fontName='BodyBold', fontSize=15,
        leading=19, textColor=NAVY, spaceAfter=9, keepWithNext=True),
    'subheading': ParagraphStyle('Subheading', fontName='BodyBold', fontSize=12,
        leading=16, textColor=NAVY, spaceBefore=8, spaceAfter=6, keepWithNext=True),
    'body': ParagraphStyle('Body', fontName='Body', fontSize=11,
        leading=14.5, textColor=INK, spaceAfter=8),
    'source': ParagraphStyle('Source', fontName='Body', fontSize=9,
        leading=12, textColor=colors.HexColor('#515c69'), spaceAfter=7),
    'subtitle': ParagraphStyle('Subtitle', fontName='Body', fontSize=10,
        leading=13, textColor=INK, spaceAfter=10),
    'code': ParagraphStyle('Code', fontName='Mono', fontSize=9,
        leading=11.7, textColor=INK, spaceBefore=3, spaceAfter=9),
    'cell': ParagraphStyle('Cell', fontName='Body', fontSize=9.5,
        leading=12.6, textColor=INK),
    'nav': ParagraphStyle('Nav', fontName='Body', fontSize=9,
        leading=12, textColor=BLUE),
}


def anchor(text):
    return re.sub(r'[^a-z0-9]+', '-', text.lower()).strip('-')


def link_uri(target):
    if target.startswith(('https://', 'http://', '#')):
        return target
    path, _, fragment = target.partition('#')
    resolved = (HERE / unquote(path)).resolve()
    if not resolved.exists():
        raise FileNotFoundError(resolved)
    return resolved.as_uri() + ('#' + fragment if fragment else '')


INLINE = re.compile(r'`[^`]+`|\*\*.+?\*\*|\[[^\]]+\]\([^)]+\)|\$[^$]+\$')


def markup(text):
    pieces = []
    pos = 0
    for token in INLINE.finditer(text):
        pieces.append(escape(text[pos:token.start()]))
        value = token.group()
        if value.startswith('`'):
            pieces.append('<font name="Mono">' + escape(value[1:-1]) + '</font>')
        elif value.startswith('**'):
            pieces.append('<b>' + escape(value[2:-2]) + '</b>')
        elif value.startswith('$'):
            formula = escape(value[1:-1])
            formula = re.sub(r'\^\{([^}]+)\}', r'<super>\1</super>', formula)
            formula = re.sub(r'\^([A-Za-z0-9])', r'<super>\1</super>', formula)
            pieces.append(formula)
        else:
            label, target = re.fullmatch(r'\[([^\]]+)\]\(([^)]+)\)', value).groups()
            uri = escape(link_uri(target), quote=True)
            pieces.append(f'<link href="{uri}" color="#0563C1">{escape(label)}</link>')
        pos = token.end()
    pieces.append(escape(text[pos:]))
    return ''.join(pieces)


def memory_diagram(deep):
    d = Drawing(WIDTH, 125)
    fill = colors.HexColor('#f3f6fa')
    for y, label in [(78, 's1.cgpaptr'), (25, 's2.cgpaptr')]:
        d.add(Rect(10, y, 145, 32, strokeColor=NAVY, fillColor=fill))
        d.add(String(24, y + 11, label, fontName='Mono', fontSize=10, fillColor=INK))
    targets = [78, 25] if deep else [52]
    for y in targets:
        d.add(Rect(326, y, 135, 32, strokeColor=NAVY, fillColor=colors.white))
        d.add(String(344, y + 11, 'double: 8.19', fontName='Mono', fontSize=10,
                     fillColor=INK))
    for sy, ty in [(94, 94 if deep else 68), (41, 41 if deep else 68)]:
        d.add(Line(155, sy, 322, ty, strokeColor=NAVY, strokeWidth=1.2))
        d.add(Polygon([326, ty, 317, ty + 4, 317, ty - 4],
                      strokeColor=NAVY, fillColor=NAVY))
    return d


diagram_folder = HERE / 'diagrams'
diagram_folder.mkdir(exist_ok=True)
for filename, deep in [('shallow-copy.svg', False), ('deep-copy.svg', True)]:
    renderSVG.drawToFile(memory_diagram(deep), str(diagram_folder / filename))

content = (HERE / 'companion.md').read_text(encoding='utf-8-sig')
section_titles = re.findall(r'^## (.+)$', content, re.M)
TOTAL_PAGES = len(section_titles)
toc_labels = section_titles
outline_groups = {
    'Storage size: bytes and bits': 'Type sizes',
    'Classes, objects, state, and behavior': 'Objects, construction, and copying',
    'Function overloading': 'Compile-time polymorphism',
    'Function overriding': 'Runtime polymorphism and abstraction',
    'Local static variables': 'Static, friendship, and lifetime',
    'Reading map': 'Reading and practice',
}

# Require the measured values and traces that the text reports.
verified = json.loads((ROOT / 'tmp/cpp-topic-builds/verification.json').read_text(
    encoding='utf-8-sig'))
code_folder = ROOT / 'Projects/CppOOP/code'
for relative, expected_hash in verified['_source_hashes'].items():
    actual_hash = hashlib.sha256((code_folder / relative).read_bytes()).hexdigest()
    assert actual_hash == expected_hash, 'Refresh code/verify.ps1: ' + relative
size_output = verified['type_sizes']
for expected in ['CHAR_BIT = 8', 'int | 4', 'long int | 4', 'double | 8',
                 'long double | 8', 'sizeof(StudentHandle) = 40',
                 'sizeof(ExamplePadding) = 8', '8.18999999999999950262']:
    assert expected in size_output, expected
assert 'Same CGPA address: false' in verified['deep_copy']
assert 'After change\nName: Rahul\nCGPA: 8.19\nName: Rahul copy\nCGPA: 9.2' in verified['deep_copy']
assert 'Same CGPA address: true' in verified['shallow_copy']
assert 'Salary after rejected update: 20000' in verified['encapsulation']
assert 'int 6\nchar k' in verified['function_overloading']
expected_traces = {
    'constructor_overloading': 's1 name: Unknown\ns2 name: Kapil',
    'operator_overloading': 'Total points: 50\nOriginal points: 20, 30',
    'function_overriding': 'Through parent reference\nchild class',
    'virtual_functions': 'Through parent pointer\nparent class\nhello from child',
    'abstraction': 'Drawing a circle',
    'static_local_variables': 'Static visits: 3, automatic visits: 1',
    'static_members': 'Names: Kapil, Rahul\nTotal created: 2',
    'friend_function': 'Salary: 20000',
    'friend_class': 'Payroll salary: 20000',
    'object_lifetime': 'Leaving inner block\nDestroying Rahul',
}
for topic, expected in expected_traces.items():
    assert expected in verified[topic], topic
source_files = {p.relative_to(code_folder).as_posix()
                for p in code_folder.glob('*/main.cpp')}
assert source_files.issubset(verified['_source_hashes']), 'Verify every topic.'


class Heading(Paragraph):
    def __init__(self, title, index):
        super().__init__(markup(f'{index}. {title}'), styles['heading'])
        self.section_title = title
        self.index = index
        self.anchor = anchor(title)

    def draw(self):
        if self.section_title in outline_groups:
            group = outline_groups[self.section_title]
            group_anchor = 'part-' + str(self.index)
            self.canv.bookmarkPage(group_anchor)
            self.canv.addOutlineEntry(group, group_anchor, 0, False)
        self.canv.bookmarkPage(self.anchor)
        self.canv.addOutlineEntry(self.section_title, self.anchor, 1, False)
        super().draw()


class ReadingDoc(SimpleDocTemplate):
    def afterFlowable(self, flowable):
        if isinstance(flowable, Heading):
            self.section_pages[flowable.section_title] = self.page


def make_table(rows):
    columns = len(rows[0])
    if columns == 4:
        widths = [151, 111, 109, WIDTH - 371]
    elif columns == 3:
        if rows[0][1] == 'Measured bytes':
            widths = [144, 79, WIDTH - 223]
        elif rows[0][1] == 'Book, edition, and section':
            widths = [142, 238, WIDTH - 380]
        else:
            widths = [164, 143, WIDTH - 307]
    else:
        widths = [190, WIDTH - 190]
    converted = [[Paragraph(markup('**' + cell + '**' if row == 0 else cell),
        styles['cell']) for cell in cells] for row, cells in enumerate(rows)]
    t = Table(converted, colWidths=widths, repeatRows=1, hAlign='LEFT')
    t.setStyle(TableStyle([
        ('BACKGROUND', (0, 0), (-1, 0), colors.HexColor('#e8eef7')),
        ('LINEBELOW', (0, 0), (-1, -1), 0.3, colors.HexColor('#ccd4df')),
        ('VALIGN', (0, 0), (-1, -1), 'TOP'),
        ('LEFTPADDING', (0, 0), (-1, -1), 6),
        ('RIGHTPADDING', (0, 0), (-1, -1), 6),
        ('TOPPADDING', (0, 0), (-1, -1), 6),
        ('BOTTOMPADDING', (0, 0), (-1, -1), 6),
    ]))
    return t


def contents_table():
    rows = []
    half = (TOTAL_PAGES + 1) // 2
    for i in range(half):
        cells = []
        for j in (i, i + half):
            if j < TOTAL_PAGES:
                href = '#' + anchor(section_titles[j])
                cells.extend([Paragraph(
                    f'<link href="{href}" color="#0563C1">{j+1}. {toc_labels[j]}</link>',
                    styles['nav']), Paragraph(str(j + 1), styles['nav'])])
            else:
                cells.extend(['', ''])
        rows.append(cells)
    t = Table(rows, colWidths=[WIDTH / 2 - 22, 22, WIDTH / 2 - 22, 22], hAlign='LEFT')
    t.setStyle(TableStyle([
        ('VALIGN', (0, 0), (-1, -1), 'TOP'),
        ('LEFTPADDING', (0, 0), (-1, -1), 0),
        ('RIGHTPADDING', (0, 0), (-1, -1), 3),
        ('TOPPADDING', (0, 0), (-1, -1), 3),
        ('BOTTOMPADDING', (0, 0), (-1, -1), 3),
    ]))
    return t


lines = content.splitlines()
story = []
i = 0
section = 0
while i < len(lines):
    line = lines[i].strip()
    if not line:
        i += 1
        continue
    if line == '<!-- page -->':
        story.append(PageBreak())
        i += 1
    elif line == '<!-- contents -->':
        story.extend([contents_table(), Spacer(1, 13)])
        i += 1
    elif line.startswith('# '):
        story.append(Paragraph(markup(line[2:]), styles['title']))
        i += 1
    elif line.startswith('## '):
        section += 1
        story.append(Heading(line[3:], section))
        i += 1
    elif line.startswith('### '):
        story.append(Paragraph(markup(line[4:]), styles['subheading']))
        i += 1
    elif line.startswith('```'):
        code = []
        i += 1
        while not lines[i].startswith('```'):
            code.append(lines[i])
            i += 1
        for code_line in code:
            if pdfmetrics.stringWidth(code_line, 'Mono', 9) > WIDTH:
                raise ValueError('Code line exceeds the page width: ' + code_line)
        story.append(KeepTogether([Preformatted('\n'.join(code), styles['code'])]))
        i += 1
    elif line.startswith('|'):
        rows = []
        while i < len(lines) and lines[i].strip().startswith('|'):
            cells = [c.strip() for c in lines[i].strip().strip('|').split('|')]
            if not all(re.fullmatch(r':?-+:?', c) for c in cells):
                rows.append(cells)
            i += 1
        story.extend([make_table(rows), Spacer(1, 9)])
    elif line.startswith('!['):
        caption, relative = re.fullmatch(r'!\[([^\]]+)\]\(([^)]+)\)', line).groups()
        image_path = (HERE / relative).resolve()
        if relative.endswith('.svg'):
            story.extend([memory_diagram('deep-copy' in relative), Spacer(1, 6)])
        else:
            with PILImage.open(image_path) as img:
                image_width, image_height = img.size
            max_width = 282 if 'encapsulation/' in relative else WIDTH
            scale = min(max_width / image_width, 1)
            story.extend([Image(str(image_path), width=image_width * scale,
                height=image_height * scale, hAlign='LEFT'), Spacer(1, 7)])
        i += 1
    else:
        paragraph = []
        while i < len(lines) and lines[i].strip() and not lines[i].strip().startswith(
                ('#', '|', '```', '![', '<!--')):
            paragraph.append(lines[i].strip())
            i += 1
        text = ' '.join(paragraph)
        if not paragraph:
            raise ValueError('Unsupported Markdown line: ' + lines[i])
        style = styles['source'] if text.startswith(('**Source', '**Further sources',
                '**Primary reference')) else styles['body']
        if not section:
            style = styles['subtitle']
        story.append(Paragraph(markup(text), style))


def footer(canvas, doc):
    canvas.saveState()
    canvas.setStrokeColor(colors.HexColor('#d4dce7'))
    canvas.line(56.7, 43, A4[0] - 56.7, 43)
    canvas.setFont('Body', 8)
    canvas.setFillColor(colors.HexColor('#515c69'))
    canvas.drawString(56.7, 30, 'C++ types and object-oriented basics')
    canvas.drawRightString(A4[0] - 56.7, 30, f'{doc.page} / {TOTAL_PAGES}')
    canvas.restoreState()


candidate = WORK / 'main-reviewed.pdf'
doc = ReadingDoc(str(candidate), pagesize=A4, leftMargin=56.7, rightMargin=56.7,
    topMargin=47, bottomMargin=58, title='C++ type sizes and object-oriented basics',
    author='', pageCompression=1)
doc.section_pages = {}
doc.build(story, onFirstPage=footer, onLaterPages=footer)
reader = PdfReader(candidate)
print('Actual pages:', len(reader.pages))
print('Section destinations:', doc.section_pages)
assert len(reader.pages) == TOTAL_PAGES, 'Review the pagination before delivery.'
for n, heading in enumerate(section_titles, 1):
    assert doc.section_pages[heading] == n, (heading, doc.section_pages[heading], n)
    assert heading in reader.pages[n - 1].extract_text(), heading
assert len(reader.outline) == 2 * len(outline_groups)
for page in reader.pages:
    assert '/Font' in page['/Resources']
    assert '\ufffd' not in (page.extract_text() or '')

pdf = pdfium.PdfDocument(str(candidate))
for n in range(len(pdf)):
    pdf[n].render(scale=1.6).to_pil().save(WORK / f'page-{n+1:02}.png')
(WORK / 'section-pages.json').write_text(json.dumps(doc.section_pages, indent=2),
    encoding='utf-8')
print('Candidate built and all pages rendered:', candidate)
