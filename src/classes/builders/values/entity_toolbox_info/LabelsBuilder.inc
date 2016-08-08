<?php

/**
 * Class LabelsValueBuilder
 *
 */
class LabelsValueBuilder extends ArrayBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, 'labels', $rawData);
  }

  /** {{@inheritdoc}} */
  protected function setValuesBuilders() {
    $this->valuesBuilders['single'] = new LabelBuilderSingle($this->entityType, $this->rawData);
    $this->valuesBuilders['plural'] = new LabelBuilderPlural($this->entityType, $this->rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->processedValueData['single'] = $this->getValueBuilder('single')
                                               ->build();
    $this->processedValueData['plural'] = $this->getValueBuilder('plural')
                                               ->build();

    return $this->processedValueData;
  }
}