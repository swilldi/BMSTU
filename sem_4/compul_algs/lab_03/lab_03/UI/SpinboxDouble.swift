import SwiftUI

struct SpinboxDouble: View {
    @Binding var value: Double
    var min: Double = 0
    var max: Double = 100
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
                        if let n = Double(text) {
                            value = Swift.min(Swift.max(n, min), max)
                        }
                        text = String(format: "%.3f", value)
                    }
                    .onAppear {
                        text = String(format: "%.3f", value)
                }
            }
            VStack {
                Button("+") {
                    if value < max { value += 0.1 }
                    text = String(format: "%.3f", value)
                }
                
                Button("-") {
                    if value > min { value -= 0.1 }
                    text = String(format: "%.3f", value)
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
