import SwiftUI

struct SpinBox: View {
    @Binding var value: Int
    var min: Int = 0
    var max: Int = 100
    var label: String = ""

    @State private var text: String = ""
    
    var body: some View {
        HStack {
            VStack {
                if !label.isEmpty {
                    Text(label)
                }
                    
                TextField("", text: $text)
                    .multilineTextAlignment(.center)
                    .frame(width: 80)
                    .textFieldStyle(.roundedBorder)
                    .onSubmit {
                        if let n = Int(text) {
                            value = Swift.min(Swift.max(n, min), max)
                        }
                        text = "\(value)"
                    }
                    .onAppear {
                        text = "\(value)"
                }
            }
            VStack {
                Button("+") {
                    if value < max { value += 1 }
                    text = "\(value)"
                }
                
                Button("-") {
                    if value > min { value -= 1 }
                    text = "\(value)"
                }
            }
        }
    }
}

// Использование:
#Preview {
    @Previewable @State var number = 5
    SpinBox(value: $number, min: 0, max: 10, label: "Количество:")
}
