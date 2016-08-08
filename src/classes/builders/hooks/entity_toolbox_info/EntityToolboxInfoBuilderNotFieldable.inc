<?php

/**
 * Class EntityToolboxInfoBuilderNotFieldable
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilderNotFieldable extends EntityToolboxInfoBuilder {
  /** {{@inheritdoc}} */
  public function __construct($entityType, array $rawData = array()) {
    parent::__construct($entityType, $rawData);
  }

  /** {{@inheritdoc}} */
  public function build() {
    parent::build();
    $this->processedData['fieldable']        = FALSE;
    $this->processedData['has_revisions']    = !empty($this->rawData['has_revisions']) ? $this->rawData['has_revisions'] : FALSE;
    $this->processedData['has_translations'] = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : FALSE;
    $this->processedData['exportable']       = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : TRUE;
    $this->processedData['bundle_entity']    = !empty($this->rawData['has_translations']) ? $this->rawData['has_translations'] : preg_replace('/_type/', '', $this->entityType);
    $this->processedData['module']           = '';
    $this->processedData['classes']          = '';
    $this->processedData['properties']       = '';
    $this->processedData['callbacks']        = '';
    $this->processedData['operations']       = '';
    $this->processedData['keys']             = '';
    $this->processedData['group']            = '';

    return array_merge($this->processedData, $this->rawData);
  }
}