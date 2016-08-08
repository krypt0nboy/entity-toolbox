<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  protected function setValuesBuilders() {
    parent::setValuesBuilders();
    $this->valuesBuilders['properties'] = new PropertiesValueBuilderFieldable($this->entityType, $this->rawData);
    $this->valuesBuilders['callbacks']  = new CallbacksValueBuilder($this->entityType, $this->rawData);
    $this->valuesBuilders['operations'] = new OperationsValueBuilder($this->entityType, $this->rawData);
    $this->valuesBuilders['keys']       = new KeysValueBuilder($this->entityType, $this->rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    parent::build();
    $this->processedData['fieldable']        = TRUE;
    $this->processedData['has_revisions']    = !empty($this->rawData['has_revisions']) ? $this->rawData['has_revisions'] : TRUE;
    $this->processedData['has_translations'] = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : TRUE;
    $this->processedData['exportable']       = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : FALSE;
    $this->processedData['bundle_entity']    = !empty($this->rawData['bundle_entity']) ? $this->rawData['bundle_entity'] : $this->entityType . "_type";
    $this->processedData['properties']       = $this->getValueBuilder('properties')
                                                    ->build();
    $this->processedData['callbacks']        = $this->getValueBuilder('callbacks')
                                                    ->build();
    $this->processedData['operations']       = $this->getValueBuilder('operations')
                                                    ->build();
    $this->processedData['keys']             = $this->getValueBuilder('keys')
                                                    ->build();

    return array_merge($this->processedData, $this->rawData);
  }

}