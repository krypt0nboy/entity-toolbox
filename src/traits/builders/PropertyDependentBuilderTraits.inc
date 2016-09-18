<?php

/**
 * Class PropertyDependentBuilderTraits
 */
trait PropertyDependentBuilderTraits {
  /**
   * Extracts the info from toolbox_info.
   *
   * @return array
   */
  public function extractToolboxInfoPropertyTemplateVars() {
    $flattened = $this->extractTemplateVars($this->toolboxInfo['properties'][$this->propertyName], '', 'property_');

    return $flattened;
  }
}