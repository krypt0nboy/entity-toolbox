<?php

/**
 * Class LabelBuilder
 */
class LabelBuilder extends StringValueBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, $tableKey, array $rawData = array(), $defaultValue = NULL, $defaultValueIsTemplate, array $templateVariables = array()) {
    parent::__construct($entityType, $tableKey, $rawData, $defaultValue, $defaultValueIsTemplate, $templateVariables);
  }

  /** {{@inheritdoc}} */
  protected function extractRawDataValue() {
    if (!empty($this->rawData['labels'][$this->tableKey])) {
      $this->rawValueData = $this->rawData['labels'][$this->tableKey];
    }
  }
}

/**
 * Class LabelBuilderSingle
 */
class LabelBuilderSingle extends LabelBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array(), $defaultValue = NULL) {
    parent::__construct($entityType, 'single', $rawData, $defaultValue);
  }

  /** {{@inheritdoc}} */
  public function build() {
    return entity_type2entity_label($this->entityType);
  }
}

/**
 * Class LabelBuilderPlural
 */
class LabelBuilderPlural extends LabelBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array(), $defaultValue = NULL) {
    parent::__construct($entityType, 'plural', $rawData, $defaultValue);
  }

  /** {{@inheritdoc}} */
  public function build() {
    return entity_type2entity_label_plural($this->entityType);
  }
}